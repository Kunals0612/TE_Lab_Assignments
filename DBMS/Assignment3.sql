CREATE TABLE Dept (
  Dept_id INT PRIMARY KEY,
  Dept_name VARCHAR(50),
  Location VARCHAR(50)
);

CREATE TABLE Employee (
  Emp_id INT PRIMARY KEY,
  Dept_id INT,
  Emp_fname VARCHAR(50),
  Emp_lname VARCHAR(50),
  Emp_position VARCHAR(50),
  Emp_salary INT,
  Emp_JoinDate DATE
);

CREATE TABLE Project (
  Proj_id INT PRIMARY KEY,
  Dept_id INT,
  Proj_name VARCHAR(50),
  Proj_Location VARCHAR(50),
  Proj_Cost INT,
  Proj_year DATE
);

INSERT INTO Dept (Dept_id, Dept_name, Location) VALUES
(1, 'COMPUTER', 'New York'),
(2, 'IT', 'San Francisco'),
(3, 'Finance', 'Chicago'),
(4, 'Marketing', 'Los Angeles'),
(5, 'Sales', 'Seattle'),
(6, 'Legal', 'Boston'),
(7, 'R&D', 'Austin'),
(8, 'Operations', 'Denver'),
(9, 'Support', 'Atlanta'),
(10, 'Logistics', 'Houston');

INSERT INTO Employee (Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_position, Emp_salary, Emp_JoinDate) VALUES
(1, 1, 'John', 'Doe', 'HR Manager', 70000, '2020-05-10'),
(2, 2, 'Jane', 'Smith', 'Software Engineer', 85000, '2019-04-15'),
(3, 3, 'Bob', 'Johnson', 'Financial Analyst', 65000, '2021-01-20'),
(4, 5, 'Alice', 'Brown', 'Marketing Specialist', 60000, '2018-11-05'),
(5, 5, 'Tom', 'White', 'Sales Representative', 55000, '2020-03-12'),
(6, 6, 'Sam', 'Green', 'Legal Advisor', 80000, '2017-09-23'),
(7, 7, 'Chris', 'Black', 'Research Scientist', 95000, '2022-06-30'),
(8, 8, 'Jessica', 'Davis', 'Operations Manager', 90000, '2019-08-19'),
(9, 9, 'David', 'Martinez', 'Support Engineer', 60000, '2021-10-25'),
(10, 10, 'Laura', 'Garcia', 'Logistics Coordinator', 58000, '2020-02-14');

INSERT INTO Project (Proj_id, Dept_id, Proj_name, Proj_Location, Proj_Cost, Proj_year) VALUES
(1, 1, 'Employee Engagement', 'New York', 200000, '2022-01-01'),
(2, 2, 'App Development', 'San Francisco', 500000, '2021-05-15'),
(3, 3, 'Annual Financial Report', 'Chicago', 150000, '2021-12-01'),
(4, 4, 'Ad Campaign', 'Los Angeles', 300000, '2022-06-10'),
(5, 5, 'Sales Strategy', 'Seattle', 250000, '2021-09-30'),
(6, 6, 'Compliance Audit', 'Boston', 100000, '2022-03-20'),
(7, 7, 'Product Research', 'Austin', 750000, '2023-02-01'),
(8, 8, 'Warehouse Operations', 'Denver', 400000, '2021-07-15'),
(9, 9, 'Customer Support Optimization', 'Atlanta', 350000, '2022-11-05'),
(10, 10, 'Supply Chain Overhaul', 'Houston', 600000, '2023-04-18');

-- Find Employee details and Department details using NATURAL JOIN.
select * from Employee e join Dept d on e.dept_id = d.dept_id;

-- Find the emp_fname,Emp_position,location,Emp_JoinDate who have same Dept id.
select e.Emp_fname, e.Emp_position, d.location, e.Emp_JoinDate from Employee e inner join Dept d on e.dept_id = d.dept_id where d.dept_id in (select dept_id from Employee group by dept_id having count(*) > 1);

-- Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’.
select e.Emp_id, e.Emp_fname, e.Emp_lname, e.Emp_position, p.Proj_id, p.Proj_Cost from Employee e inner join Project p on e.Dept_id = p.Dept_id where p.Proj_name != "Hyderabad";

-- Find Department Name ,employee name, Emp_position for which project year is 2021
select d.Dept_name, e.Emp_fname, e.Emp_position from Employee e inner join Dept d on e.Dept_id = d.Dept_id where d.Dept_id in (select Dept_id from Project where year(Proj_year) = 2021);

-- Display emp_position,D_name who have Project cost >300000
select e.Emp_position, d.Dept_name from Employee e inner join Dept d on e.Dept_id = d.Dept_id where d.Dept_id in (select Dept_id from Project where Proj_Cost > 300000);

-- Find the names of all the Projects that started in the year 2015.
select * from Project where year(Proj_year) = 2022;

-- List the Dept_name having no_of_emp=2
select d.Dept_name from Employee e inner join Dept d on e.Dept_id = d.Dept_id group by e.Dept_id having count(*) = 2;

-- Display the total number of employee who have joined any project before 2022
select count(*) as total_employee_before_2022 from Employee e inner join Project p on e.Dept_id = p.Dept_id where year(p.Proj_year) < 2022;

-- Create a view showing the employee and Department details.
create view EmployeeDeptDetails as select e.Emp_id, e.Emp_fname, e.Emp_lname, e.Emp_position, e.Emp_salary, e.Emp_JoinDate, e.Dept_id, d.Dept_name, d.Location from Employee e inner join Dept d on e.Dept_id = d.Dept_id;
select * from EmployeeDeptDetails;

-- Perform Manipulation on simple view-Insert, update, delete, drop view.
CREATE VIEW SimpleEmployeeView AS
SELECT Emp_id, Emp_fname, Emp_lname, Emp_position, Emp_salary
FROM Employee;

INSERT INTO SimpleEmployeeView (Emp_id, Emp_fname, Emp_lname, Emp_position, Emp_salary)
VALUES (11, 'Michael', 'Scott', 'Branch Manager', 90000);

DELETE FROM SimpleEmployeeView
WHERE Emp_id = 11;

DROP VIEW SimpleEmployeeView;

-- Create a complex view combining Employee, Department, and Project details
CREATE VIEW ComplexEmployeeProjectView AS
SELECT 
    e.Emp_id,
    e.Emp_fname,
    e.Emp_lname,
    e.Emp_position,
    e.Emp_salary,
    d.Dept_name,
    d.Location AS Dept_Location,
    p.Proj_name,
    p.Proj_Location,
    p.Proj_Cost
FROM 
    Employee e
INNER JOIN 
    Dept d ON e.Dept_id = d.Dept_id
INNER JOIN 
    Project p ON e.Dept_id = p.Dept_id;

-- Select data from the ComplexEmployeeProjectView
SELECT * FROM ComplexEmployeeProjectView;

