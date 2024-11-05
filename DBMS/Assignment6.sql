CREATE TABLE old_employee (
    employee_id INT PRIMARY KEY,
    name VARCHAR(50),
    salary INT
);

CREATE TABLE new_employee (
    employee_id INT PRIMARY KEY,
    name VARCHAR(50),
    salary INT
);

INSERT INTO old_employee (employee_id, name, salary) VALUES
(101, 'Alice', 50000),
(102, 'Bob', 60000),
(103, 'Charlie', 55000),
(104, 'David', 70000),
(105, 'Eve', 65000);

INSERT INTO new_employee (employee_id, name, salary) VALUES
(101, 'Alice', 50000),
(104, 'David', 70000);

DELIMITER //

-- Parameterized Procedure: Adds a specific employee to new_employee if not already present
CREATE PROCEDURE addemp_param(IN emp_id INT)
BEGIN
    DECLARE e_id INT;
    DECLARE e_name VARCHAR(50);
    DECLARE e_sal INT;
    DECLARE done INT DEFAULT 0;

    -- Declare a parameterized cursor
    DECLARE i CURSOR (cur_id INT) FOR
        SELECT employee_id, name, salary FROM old_employee WHERE employee_id = cur_id;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    -- Open cursor with the parameter
    OPEN i(emp_id);

    read_loop: LOOP
        FETCH i INTO e_id, e_name, e_sal;
        
        IF done THEN
            LEAVE read_loop;
        END IF;

        -- Insert employee if not already present in new_employee
        IF NOT EXISTS (SELECT * FROM new_employee WHERE employee_id = e_id) THEN
            INSERT INTO new_employee (employee_id, name, salary) VALUES (e_id, e_name, e_sal);
        END IF;
    END LOOP;

    CLOSE i;
END //

-- Non-Parameterized Procedure: Adds all missing employees from old_employee to new_employee
CREATE PROCEDURE addemp_non_param()
BEGIN
    DECLARE e_id INT;
    DECLARE e_name VARCHAR(50);
    DECLARE e_sal INT;
    DECLARE done INT DEFAULT 0;

    -- Non-parameterized cursor
    DECLARE i CURSOR FOR
        SELECT employee_id, name, salary FROM old_employee;

    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    OPEN i;

    read_loop: LOOP
        FETCH i INTO e_id, e_name, e_sal;
        
        IF done THEN
            LEAVE read_loop;
        END IF;

        -- Insert employee if not already present in new_employee
        IF NOT EXISTS (SELECT * FROM new_employee WHERE employee_id = e_id) THEN
            INSERT INTO new_employee (employee_id, name, salary) VALUES (e_id, e_name, e_sal);
        END IF;
    END LOOP;

    CLOSE i;
END //

DELIMITER ;
