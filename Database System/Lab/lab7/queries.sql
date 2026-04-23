--Task 1:
--(a) Display employee first name and department name using INNER JOIN.
select e.first_name,d.department_name from employees e
inner join departments d
on e.department_id = d.department_id;
--(b) Display all possible combinations of employees and jobs using CROSS JOIN.
select e.first_name,j.job_title from employees e
cross join jobs j;
--(c) Display employee name and manager name using SELF JOIN.
select e.first_name as employee_name, m.first_name as manager_name from employees e
join employees m
on e.manager_id = m.manager_id;
--(d) Display all employees and their department names including those without departments using LEFT OUTER JOIN.
select e.first_name,d.department_name from employees e
left outer join departments d
on e.department_id = d.department_id;

--Task 2:
--(a) Write a query to display department name and employee name using RIGHT OUTER JOIN 
--(to see all departments including empty ones).
select e.first_name,d.department_name from employees e
right outer join departments d
on e.department_id = d.department_id;
--(b) HR wants to analyze employees who changed jobs. Use INTERSECT between EMPLOYEES and JOB_HISTORY.
select employee_id from employees 
intersect 
select employee_id from job_history;
--(c) Find employees who never changed jobs using MINUS.
select employee_id from employees 
minus 
select employee_id from job_history;

--Task 3:
--Create a VIEW that shows: Employee full name, Department name, Job title.
create or replace view emp_details_vw as
select e.first_name || ' ' || e.last_name as full_name, d.department_name, j.job_title
from employees e
join departments d on e.department_id = d.department_id
join jobs j on e.job_id = j.job_id;

--Task 4:
--Design a report system view that uses JOIN, WHERE, 
--includes employees with salary > average (using an inline query), and uses ORDER BY.
create or replace view high_salary_reports as
select e.first_name || ' ' || e.last_name as full_name,
        d.department_name, e.salary
from employees e
join departments d on e.department_id = d.department_id 
join (select avg(salary) as avg_salary from employees) avg_table
on e.salary > avg_table.avg_salary
where d.department_name is not null
order by e.salary desc;

--Task 5:
--A view that shows only employees of department 50
--Part 1: View with Check Option
create or replace view dept50 as
select employee_id, first_name, last_name, department_id from employees
where department_id = 50
with check option;
--Part 2: UNION operation
SELECT employee_id FROM employees
UNION
SELECT employee_id FROM job_history;

--Task 6:
-- a reusable view combining multiple tables, filtering by avg salary.
create or replace view hr_performance_summary as 
select e.first_name || ' ' || e.last_name AS full_name,
       d.department_name,
       j.job_title,
       e.salary
from employees e
join departments d on e.department_id = d.department_id
join jobs j on e.job_id = j.job_id
where e.salary > (select avg(salary) from employees);

--Task 7: 
-- taking department 80 as an example
create or replace view secure_dept80_managers_vw as 
select employee_id, first_name, last_name, email, job_id, salary, department_id
from employees
where department_id = 80
with check option constraint secure_dept80_ck;

create or replace view  emp_job_timeline_vw as 
select employee_id, job_id, department_id, hire_date AS role_start_date, 
        NULL AS role_end_date, 'CURRENT' AS record_status
from employees
union all
select employee_id, job_id, department_id, 
    start_date AS role_start_date, 
    end_date AS role_end_date, 
    'HISTORICAL' AS record_status
from job_history;

