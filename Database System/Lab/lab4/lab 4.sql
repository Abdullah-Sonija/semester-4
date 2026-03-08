select * from employees where rownum <=5;

select first_name || ' ' || last_name as full_name from employees;

-- Question 3
select upper(trim(first_name || ' ' || last_name)) as full_name from employees;
-- Question 4
select first_name, email as old_email, replace(email,'@oldcompany.com','@newcompany.com') as new_email from employees;
-- Question 5
select employee_id , first_name, hire_date from employees where first_name like '%an%' 
and hire_date between to_date('2010-01-01', 'YYYY-MM-DD') and to_date('2015-12-31', 'YYYY-MM-DD');

-- Question 6
select employee_id , salary, to_char(round(salary,2),'fm999,999.00') as foramtted_salary from employees;
