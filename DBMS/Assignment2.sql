

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
    Emp_JoinDate DATE,
    FOREIGN KEY (Dept_id) REFERENCES Dept(Dept_id) ON DELETE CASCADE
);

CREATE TABLE Project (
    Proj_id INT PRIMARY KEY,
    Dept_id INT,
    Proj_name VARCHAR(50),
    Proj_Location VARCHAR(50),
    Proj_Cost INT,
    Proj_year DATE,
    FOREIGN KEY (Dept_id) REFERENCES Dept(Dept_id) ON DELETE CASCADE
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
    (4, 4, 'Alice', 'Brown', 'Marketing Specialist', 60000, '2018-11-05'),
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

-- Display Employee details with computer department
select * from Employee where dept_id in (select dept_id from Dept where Dept_name = 'COMPUTER');

-- List the number of different employee Emp_position
select Emp_position, count(*) as total_employee from Employee group by Emp_position;

-- Give 10% to employee whose joining date is less than 2020
update Employee set Emp_salary = Emp_salary + Emp_salary * 0.1 where Emp_JoinDate < "2020-01-01";
select * from Employee;
-- Delete the dept with name Chicago

-- SET FOREIGN_KEY_CHECKS = 0;

delete from Dept where Location = "Chicago";
select * from Dept;

-- SET FOREIGN_KEY_CHECKS = 1;

-- find the name of project where location is Austin
select Proj_name from Project where dept_id in(select dept_id from Dept where location = "Austin");

-- find the project having cost in between 100000 to 500000
select Proj_name from Project where Proj_Cost > 100000 and Proj_Cost < 500000;

-- find maximum and avg project cost
select max(Proj_Cost) as max_price, avg(Proj_Cost) as avg_price from Project;

-- display all the employee with Emp_id, Emp_name with decreasing order of Emp_lname
select Emp_id, Emp_fname from Employee order by Emp_lname desc;

-- display Project in 2020 2021 2022
select Proj_name, Proj_Location, Proj_Cost from Project where year(Proj_year) in (2020,2021,2022);
