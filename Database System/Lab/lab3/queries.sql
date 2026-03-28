 -- cleaning drop commands
---DROP TABLE product CASCADE CONSTRAINTS PURGE;
DROP TABLE category CASCADE CONSTRAINTS PURGE;
DROP TABLE employee CASCADE CONSTRAINTS PURGE;
DROP TABLE hr_department CASCADE CONSTRAINTS PURGE;
DROP TABLE project CASCADE CONSTRAINTS PURGE;
DROP TABLE instructor CASCADE CONSTRAINTS PURGE;
DROP TABLE Student2 CASCADE CONSTRAINTS PURGE;
DROP TABLE department CASCADE CONSTRAINTS PURGE;
DROP TABLE Student CASCADE CONSTRAINTS PURGE;
DROP TABLE Courses CASCADE CONSTRAINTS PURGE;
DROP TABLE Course CASCADE CONSTRAINTS PURGE;
PURGE RECYCLEBIN;

-- Q1: Create Course Table
CREATE TABLE Course (
    course_id int primary key,
    course_name varchar2(50) not null,
    credit_hours number
);

-- Q2: Create Student Table
CREATE TABLE Student (
    student_id int primary key,
    student_name varchar2(100) not null,
    age int check (age >= 18)
);

-- Q3 & Q4: Alter Student and Rename Course
ALTER TABLE Student ADD status varchar2(20) default 'Active';
ALTER TABLE Course RENAME TO Courses;

-- Q5: Department, Student, Instructor modifications
CREATE TABLE Department (
    dept_id int primary key,
    dept_name varchar2(40) not null
);

-- Note: Naming this Student2 because Q2 already created a 'Student' table
CREATE TABLE Student2 (
    student_id int primary key,
    student_name varchar2(60), 
    dept_id int,
    credit_hours number,
    constraint fk_dept foreign key (dept_id) references Department(dept_id)
);

-- Creating Instructor table to fulfill the ALTER requirement
CREATE TABLE Instructor (
    instructor_id int primary key,
    email varchar2(100)
);

-- Q5 Modifications:
ALTER TABLE Instructor ADD constraint ins_email_uq unique (email);
ALTER TABLE Student2 MODIFY student_name varchar2(100);
ALTER TABLE Student2 ADD constraint chk_credit_hr check (credit_hours between 1 and 4);
ALTER TABLE Student2 RENAME COLUMN student_name TO full_name;

-- Q6: Project Tracking System
CREATE TABLE Project (
    project_id int primary key,
    project_name varchar2(255) not null,
    start_date date not null,
    end_date date not null,
    budget number,
    constraint chk_budget check (budget > 10000),    
    constraint chk_dates check (end_date > start_date)
);

-- Q7: Employee and Department 
-- Note: Naming this Department_Q7 because Q5 already created a 'Department' table
CREATE TABLE Department_Q7 (
    dept_id int primary key,
    dept_name varchar2(100) not null
);

CREATE TABLE Employee (
    employee_id int primary key,
    first_name varchar2(50),
    last_name varchar2(50),
    dept_id int
);

-- Enforcing the foreign key:
ALTER TABLE Employee ADD constraint fk_emp_dept foreign key (dept_id) references Department_Q7(dept_id);

-- Q8: Product and Category
CREATE TABLE Category (
    category_id int primary key,
    category_name varchar2(100) not null
);

CREATE TABLE Product (
    product_id int primary key,
    product_name varchar2(255) not null unique,
    price number check (price > 0),
    category_id int,
    status varchar2(20) default 'Active',
    constraint fk_prod_cat foreign key (category_id) references Category(category_id)
);
