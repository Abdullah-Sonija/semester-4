set serveroutput on;

-- task 1:
-- (a) before insert trigger that displays a message
create or replace trigger trg_la_before_insert
before insert on employees
for each row
begin 
    dbms_output.put_line('Task 1a: a new employee record is being inserted.');
end;
/
-- (b) before update trigger that prints username
create or replace trigger trg_lb_before_update
before update on employees
for each row
begin 
    dbms_output.put_line('task 1b: employee record updated by user: ' || user);
end;
/
-- (c) prevent salary update if salary > 20000
create or replace trigger trg_1c_check_salary
before update of salary on employees
for each row
begin
    if :new.salary > 20000 then
        raise_application_error(-20001, 'task 1c error: salary cannot exceed 20,000.');
    end if;
end;
/
-- (d) log deleted employee records into another table
create table deleted_employees_log(
    emp_id number,
    first_name varchar2(50),
    deleted_by varchar2(50),
    delete_date date
);

create or replace trigger trg_log_deleted
before delete on employees
for each row
begin
    insert into deleted_employees_log (emp_id,first_name,deleted_by,delete_date)
    values (:old.employee_id,:old.first_name,user,sysdate);
end;
/

-- task 2:
-- (a) automatically store audit data (user + time) when a transaction is inserted
create table transaction_audit (
    username varchar2(30),
    action_time date,
    action_type varchar2(20)
);

create or replace trigger trg_audit_insert
after insert on employees
for each row
begin
    insert into transaction_audit(username,action_time,action_type)
    values (user,sysdate,'insert');
end;
/
-- (b) ddl trigger that logs all table creation
create table ddl_creation_log(
    object_name varchar2(50),
    object_type varchar2(50),
    created_by varchar2(50),
    creation_time date
);

create or replace trigger trg_log_table_creation
before create on schema
begin
    if ora_dict_obj_type = 'TABLE' then 
        insert into ddl_creation_log (object_name,object_type,created_by,creation_time)
        values (ora_dict_obj_name,ora_dict_obj_type,user,sysdate);
    end if;
end;
/
-- (c) prevent drop table operation on critical tables
create or replace trigger trg_prevent_drop
before drop on schema
begin
    if ora_dict_obj_name in ('EMPLOYEES', 'DEPARTMENTS') then 
        raise_application_error(-20002, 'task 2c error: critical tables cannot be dropped.');
    end if;
end;
/

-- task 3: 
-- create a logon trigger that stores login time
create table user_login_log(
    user_name varchar2(50),
    login_time date
);

create or replace trigger trg_login_audit
after logon on schema
begin
    insert into user_login_log (user_name,login_time)
    values (user,sysdate);
end;
/

-- tasks 4 & 6: As all the requirements of task 4 are fullfilled in the task 6
-- automatically logs insert/update/delete, stores old/new values, records 
-- user & timestamp, and differentiates operations.

create table enterprise_audit_log(
    log_id number,
    emp_id number,
    old_salary number,
    new_salary number,
    old_job_id varchar2(20),
    new_job_id varchar2(20),
    operation varchar2(20),
    ap_user varchar2(50),
    ap_date date
);

create sequence enterprise_audit_log_seq start with 1 increment by 1;

create or replace trigger trg_ent_audit_log_id
before insert on enterprise_audit_log
for each row
begin
    if :new.log_id is null then
        select enterprise_audit_log_seq.nextval into :new.log_id from dual;
    end if;
end;
/

create or replace trigger trg_4_6_enterprise_audit
after insert or update or delete on employees
for each row
declare
    v_operation varchar2(20);
begin
    if inserting then 
        v_operation := 'insert';
        insert into enterprise_audit_log (emp_id, new_salary, new_job_id, operation, ap_user, ap_date)
        values (:new.employee_id, :new.salary, :new.job_id, v_operation, user, sysdate);
        
    elsif updating then
        v_operation := 'update';
        insert into enterprise_audit_log (emp_id, old_salary, new_salary, old_job_id, new_job_id, operation, ap_user, ap_date)
        values (:new.employee_id, :old.salary, :new.salary, :old.job_id, :new.job_id, v_operation, user, sysdate);
        
    elsif deleting then
        v_operation := 'delete';
        insert into enterprise_audit_log (emp_id, old_salary, old_job_id, operation, ap_user, ap_date)
        values (:old.employee_id, :old.salary, :old.job_id, v_operation, user, sysdate);
    end if;
end;
/

-- tasks 5 & 7: As all the requirements of task 4 are fullfilled in the task 6
-- synchronized backup table, schema change logs, login/logout tracking, 
-- and instead of trigger for view modifications.

create table employees_sync_backup as select * from employees where 1=2;

create or replace trigger trg_5_7_sync_backup
after insert or update or delete on employees
for each row
begin
    if inserting then
        insert into employees_sync_backup (employee_id, first_name, last_name, salary, department_id)
        values (:new.employee_id, :new.first_name, :new.last_name, :new.salary, :new.department_id);
    elsif updating then
        update employees_sync_backup
        set first_name = :new.first_name, last_name = :new.last_name, salary = :new.salary, department_id = :new.department_id
        where employee_id = :old.employee_id;
    elsif deleting then
        delete from employees_sync_backup 
        where employee_id = :old.employee_id;
    end if;
end;
/

--
create table financial_schema_log (
    log_date date,
    username varchar2(30),
    obj_type varchar2(30),
    obj_name varchar2(100),
    operation varchar2(30)
);

create or replace trigger trg_5_7_ddl_log
after ddl on schema
begin
    insert into financial_schema_log (log_date, username, obj_type, obj_name, operation)
    values (sysdate, user, ora_dict_obj_type, ora_dict_obj_name, ora_sysevent);
end;
/

--
create table financial_sys_activity (
    username varchar2(30),
    event_type varchar2(20),
    event_time date
);

create or replace trigger trg_5_7_logon_activity
after logon on schema
begin
    insert into financial_sys_activity (username, event_type, event_time)
    values (user, 'logon', sysdate);
end;
/

--
create or replace trigger trg_5_7_logoff_activity
before logoff on schema
begin
    insert into financial_sys_activity (username, event_type, event_time)
    values (user, 'logoff', sysdate);
end;
/

create or replace view vw_emp_dept_financial as
select e.employee_id, e.first_name, e.salary, d.department_name
from employees e
join departments d on e.department_id = d.department_id;

create or replace trigger trg_5_7_instead_of_update
instead of update on vw_emp_dept_financial
for each row
begin
    update employees
    set first_name = :new.first_name,
        salary = :new.salary
    where employee_id = :old.employee_id;
end;
/
