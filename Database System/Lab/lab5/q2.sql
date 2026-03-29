select d.department_name, round(avg(e.salary), 2) as avg_salary from employees e 
join departments d on e.department_id = d.department_id group by d.department_name order by avg_salary desc;

select d.department_name, count(e.employee_id) as employee_count from employees e 
join departments d on e.department_id = d.department_id group by d.department_name having count(e.employee_id) > 5;


select department_id, sum(salary) as total_salary from employees group by department_id order by total_salary desc;

insert into departments (department_id, department_name, manager_id, location_id) values (280, 'Data Science', 100, 1700);

update employees set salary = salary * 1.05 where department_id = 50;
