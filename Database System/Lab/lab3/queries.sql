create table Course (
    course_id int primary key,
    course_name varchar2(50) not null,
    credit_hours number
);

create table Student (
    student_id int primary key,
    student_name varchar2(100) not null,
    age int check (age >=18)
);

alter table Student add status varchar2(20) default 'Active';

alter table course rename to courses;

create table department (
    dept_id int primary key,
    dept_name varchar2(40) not null
    );
    
create table Student2 (
    student_id int primary key,
    student_name varchar2(60) not null,
    dept_id int,
    constraint fk_dpet foreign key (dept_id) references department(dept_id),
    credit_hours number
);

create table instructor (
    instructor_id int primary key,
    email varchar2(100)
);

alter table instructor add constraint ins_email unique (email);

alter table student2 modify student_name varchar2(100);

alter table student2 rename column student_name to full_name;

alter table student2 add constraint chk_credit_hr check (credit_hours between 1 and 4);


create table project (
    project_id int primary key,
    project_name varchar(255) not null,
    start_date date not null,
    end_date date not null,
    budget decimal(15, 2),
    
    constraint chk_budget check (budget > 10000),    
    constraint chk_dates check (end_date > start_date)
);

-- Question 7

create table department (
    departmentid int primary key,
    deptname varchar(100) not null
);

create table employee (
    employeeid int primary key,
    firstname varchar(50),
    lastname varchar(50),
    deptid int
);

desc department;

alter table employee add constraint fk_employee_department foreign key (deptid) references department (departmentid);

-- Question 8
create table category (
    category_id int primary key,
    category_name varchar(100) not null
);

create table product (
    product_id int primary key,
    product_name varchar(255) not null unique,
    price decimal(10, 2) check (price > 0),
    category_id int,
    status varchar(20) default 'active',
    constraint fk_product_category foreign key (category_id) references category (category_id)
);
