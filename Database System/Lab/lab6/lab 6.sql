-- Question 1
-- part a
select * from employees where department_id = 60;
select * from departments where department_id = 60;
select max(hire_date) from employees where department_id = 60;

select * from employees where hire_date > (select max(hire_date) from employees where department_id = 60);

-- part b

select avg(salary) from employees where job_id = 'SA_REP';
select * from employees where salary > (select avg(salary) from employees where job_id = 'SA_REP');

-- part c

select department_id from employees where employee_id = 103;

select * from employees where department_id = (select department_id from employees where employee_id = 103);


-- part d

select avg(salary) from employees;

select job_title , min_salary from jobs where min_salary > (select avg(salary) from employees);


-- part e
select min_salary from jobs;

select * from employees where salary in (select min_salary from jobs);


-- Question 2
-- part a

select * from employees where employee_id = 101;
select manager_id from employees where employee_id = 101;

select * from employees where manager_id = (select manager_id from employees where employee_id = 101);


-- part b

select * from employees e where (select count(distinct manager_id) from employees i where e.department_id = i.department_id) > 1;
-- using group by
select department_id from employees group by department_id having count(distinct manager_id) > 1;
select * from employees where department_id in (select department_id from employees group by department_id having count(distinct manager_id) > 1);

-- part c

select avg(salary) from employees where department_id = 90;

select department_id, avg(salary) from employees group by department_id having avg(salary) > 
    (select avg(salary) from employees where department_id = 90);

-- part d
select median(salary) from employees;
select * from employees where salary > (select median(salary) from employees);

-- part e
select avg(commission_pct) from employees;
select * from employees where commission_pct > (select avg(commission_pct) from employees);


-- part f
select * from departments;
select location_id from departments where department_name = 'Marketing';
select department_id from departments where location_id = (select location_id from departments where department_name = 'Marketing');

select * from employees where department_id in
    (select department_id from departments where location_id = 
        (select location_id from departments where department_name = 'Marketing'));

-- part g
select * from employees where salary not in (select salary from employees where department_id = 50 and salary is not null);

-- part h
select avg(salary) from employees where department_id = 10;
select avg(salary) from employees where department_id = 20;
select * from employees where salary between 
    (select avg(salary) from employees where department_id = 10) and (select avg(salary) from employees where department_id = 20);


-- part i
select * from employees e where exists (select 1 from job_history jh where jh.employee_id = e.employee_id);



-- Question 3
select * from employees e where 
    e.department_id in
    (select department_id from employees group by department_id having avg(salary) > 
        (select avg(salary) from employees)
    )
    and e.salary >
    (select avg(salary) from employees i where i.department_id = e.department_id)
    and e.hire_date < add_months(to_date('2026-03-06','yyyy-mm-dd'), - 120)
    and not exists (select 1 from job_history jh where jh.employee_id = e.employee_id)
    and not exists (select 1 from employees m where m.manager_id = e.employee_id)
;  

-- Question 4
select avg(salary) from employees;

select department_id, max(salary), min(salary) from employees group by department_id 
    having max(salary) > (select avg(salary) from employees)
    and min(salary) < (select avg(salary) from employees);


-- Question 5
select department_id, sum(salary) as total_expense from employees 
group by department_id having sum(salary) > (select max(salary) from employees);
select * from employees e where 
    salary < (select max(salary) from employees i where i.department_id = e.department_id) and salary > (select avg(salary) from employees i where i.department_id = e.department_id);  
select * from employees e where not exists (select 1 from employees n where n.manager_id = e.employee_id);
select * from employees where salary > (select max(salary) from employees where department_id = 30);
select * from employees e where exists 
    (select 1 from departments d1 where d1.department_id = e.department_id and exists 
        (select 1 from departments d2 where d1.department_id <> d2.department_id and d2.location_id = d1.location_id)
    );
--
select * from employees e where
    e.department_id in
    (select department_id as total_expense from employees 
     group by department_id having sum(salary) > (select max(salary) from employees) )
    and e.salary < (select max(salary) from employees i where i.department_id = e.department_id)
    and e.salary > (select avg(salary) from employees i where i.department_id = e.department_id)
    and not exists (select 1 from employees n where n.manager_id = e.employee_id)
    and e.salary > (select max(salary) from employees where department_id = 30)
    and  exists 
    (select 1 from departments d1 where d1.department_id = e.department_id and exists 
        (select 1 from departments d2 where d1.department_id <> d2.department_id and d2.location_id = d1.location_id)
    )
;

-- Question 6

select department_id , (max(salary) - min(salary)) as salary_gap from employees group by department_id
having (max(salary) - min(salary)) > (select avg(salary) from employees);

select * from employees e where salary > (select median(salary) from employees d where e.department_id = d.department_id);

select * from employees e where salary < (select max(salary) from employees d where e.department_id = d.department_id);

select * from employees e where not exists (select 1 from job_history);

select * from employees e where
    e.department_id in (
        select department_id from employees 
        group by department_id 
        having (max(salary) - min(salary)) > (select avg(salary) from employees)
    )
    and e.salary > (select median(salary) from employees d where d.department_id = e.department_id)
    and e.salary < all (select max(salary) from employees m where m.department_id = e.department_id)
    and not exists (select 1 from job_history jh where jh.employee_id = e.employee_id)
    and e.department_id in (select department_id from employees group by department_id having min(salary) > 4000)
;


-- Question 7

select * from employees e where
    e.department_id in (
        select department_id 
        from employees 
        group by department_id 
        having avg(salary) > (select avg(salary) from employees)
    )
    and e.salary > (select avg(salary) from employees d where d.department_id = e.department_id)
    and e.salary < (select max(salary) from employees)
    and e.salary > all (select salary from employees where department_id = 20)
    and e.hire_date < (select m.hire_date from employees m where m.employee_id = e.manager_id)
    and exists (
        select 1 from employees h 
        where h.department_id = e.department_id 
        and h.hire_date > to_date('31-12-2020', 'dd-mm-yyyy')
    )
    and not exists (select 1 from employees n where n.manager_id = e.employee_id)
    and not exists (select 1 from job_history jh where jh.employee_id = e.employee_id)
;
