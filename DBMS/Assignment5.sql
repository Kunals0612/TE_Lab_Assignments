-- Create the Stud_Marks table
CREATE TABLE Stud_Marks (
    roll_no INT PRIMARY KEY,      -- Primary key for unique roll number
    name VARCHAR(50),             -- Name of the student
    total_marks INT               -- Total marks obtained by the student
);

-- Insert sample data into Stud_Marks
INSERT INTO Stud_Marks (roll_no, name, total_marks) 
VALUES 
(1, 'John Doe', 1000),
(2, 'Jane Smith', 950),
(3, 'Michael Johnson', 875),
(4, 'Emily Davis', 820),
(5, 'David Brown', 1200);

-- Create the Result table to store the output from the procedure
CREATE TABLE Result (
    roll_no INT PRIMARY KEY,      -- Primary key for unique roll number
    name VARCHAR(50),             -- Name of the student
    grade VARCHAR(50)             -- Grade determined by the procedure
);

-- Create the function to determine the grade based on marks
DELIMITER //
CREATE FUNCTION processGrade(marks INT)
RETURNS VARCHAR(50)
BEGIN
    -- Determine grade based on the total marks
    IF marks BETWEEN 990 AND 1500 THEN
        RETURN 'Distinction';
    ELSEIF marks BETWEEN 900 AND 989 THEN
        RETURN 'First Class';
    ELSEIF marks BETWEEN 825 AND 899 THEN
        RETURN 'Higher Second Class';
    ELSE
        RETURN 'Lower Class';
    END IF;
END //
//
DELIMITER ;

-- Create the procedure to display the result and insert it into the Result table
DELIMITER //
CREATE PROCEDURE display_res(IN rollnum INT)
BEGIN
    DECLARE grade VARCHAR(50);
    DECLARE tm INT;
    DECLARE newName VARCHAR(50);
    
    -- Get total marks and name for the given roll number
    SELECT total_marks INTO tm FROM Stud_Marks WHERE roll_no = rollnum;
    SELECT name INTO newName FROM Stud_Marks WHERE roll_no = rollnum;
    
    -- Determine the grade using the function
    SET grade = processGrade(tm);
    
    -- Insert the result into the Result table
    INSERT INTO Result (roll_no, name, grade)
    VALUES (rollnum, newName, grade);
END //
//
DELIMITER ;

-- Example call to the procedure
CALL display_res(1); -- Replace with any roll number to test
