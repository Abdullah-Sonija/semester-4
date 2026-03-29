1.	select department_id, sum(salary) as total_salary, avg(salary) as average_salary from employees group by department_id having avg(salary) > 7000;
2.	select * from departments where department_id = 280;
3.	select d.department_name, count(e.employee_id) from employees e join departments d on e.department_id = d.department_id where e.salary > 5000 group by d.department_name having count(e.employee_id) > 3;
4.	create table employees_backup_table as select * from employees;
select * from employees_backup_table;
5. select department_id, avg(salary) as avg_dept_salary from employees where job_id <> 'IT_PROG' group by department_id having avg(salary) > 5000 order by avg_dept_salary desc;
