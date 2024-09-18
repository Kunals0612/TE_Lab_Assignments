CREATE TABLE Stud_Marks (
    roll_no INT PRIMARY KEY,
    name VARCHAR(50),
    total_marks INT
);

INSERT INTO Stud_Marks (roll_no, name, total_marks) 
VALUES 
(1, 'John Doe', 1000),
(2, 'Jane Smith', 950),
(3, 'Michael Johnson', 875),
(4, 'Emily Davis', 820),
(5, 'David Brown', 1200);


DELIMITER //

CREATE PROCEDURE proc_Grade(IN roll INT, OUT Grade VARCHAR(50))
BEGIN
    DECLARE studMarks INT;
    
    -- Fetch total_marks into the variable studMarks
    SELECT total_marks INTO studMarks FROM Stud_Marks WHERE roll_no = roll;
    
    -- Determine grade based on the total marks
    IF studMarks BETWEEN 990 AND 1500 THEN
        SET Grade = 'Distinction';
    ELSEIF studMarks BETWEEN 900 AND 989 THEN
        SET Grade = 'FirstClass';
    ELSEIF studMarks BETWEEN 835 AND 899 THEN
        SET Grade = 'HigherSecondClass';
    ELSE
        SET Grade = 'LowerClass';
    END IF;
END //

DELIMITER ;

DELIMITER //

CREATE FUNCTION func_Grade(rollnumber INT)
RETURNS VARCHAR(50)
BEGIN
    DECLARE Grade VARCHAR(50);
    
    -- Call the procedure to get the grade
    CALL proc_Grade(rollnumber, @kunal);
    
    -- Return the value stored in the variable @kunal
    RETURN @kunal;
END //

DELIMITER ;

SELECT roll_no, name, total_marks, func_Grade(roll_no) AS Class 
FROM Stud_Marks;
