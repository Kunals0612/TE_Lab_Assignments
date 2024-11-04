CREATE TABLE borrower (
    roll_no INT,
    name VARCHAR(50),
    doi DATE,
    book_name VARCHAR(50),
    status VARCHAR(1) DEFAULT 'I'
);

CREATE TABLE fine (
    roll_no INT,
    date DATE,
    amt INT
);

INSERT INTO borrower VALUES 
	(1,'deleniti','2012-07-03','enim',0),
	(2,'harum','1998-02-27','magnam',1),
	(3,'velit','1993-10-19','minus',0),
	(4,'ullam','2002-09-10','incidunt',0),
	(5,'totam','1992-01-23','tempora',0),
	(6,'eos','2023-03-03','dolor',0),
	(7,'ut','1979-10-08','nostrum',1),
	(8,'debitis','1981-08-09','quae',0),
	(9,'harum','2014-11-25','voluptate',1),
	(10,'doloremque','1988-11-30','quo',1)
;



DELIMITER //

CREATE PROCEDURE library(IN roll INT, IN book VARCHAR(50))
BEGIN
    DECLARE fine INT;
    DECLARE dt2 INT;
    
    -- Exit handler for foreign key constraint error (error code 1452)
    DECLARE EXIT HANDLER FOR 1452 
    SELECT 'Primary key not found' AS ErrorMessage;

    -- Fetch the date of issue (doi) from the Borrower table based on roll_no and book_name
    SELECT @idt := doi 
    FROM Borrower 
    WHERE roll_no = roll AND book_name = book;

    -- Fetch the status from the Borrower table
    SELECT @stt := status 
    FROM Borrower 
    WHERE roll_no = roll AND book_name = book;

    -- Calculate the difference in days between the current date and issue date
    SET dt2 := DATEDIFF(CURDATE(), @idt);

    -- If the book has not been returned
    IF @stt = FALSE THEN
        IF dt2 <= 14 THEN
            SET fine := 0;  -- No fine if returned within 14 days
        ELSEIF dt2 BETWEEN 15 AND 30 THEN
            SET fine := (dt2 - 14) * 5;  -- Rs 5 per day for days 15 to 30
        ELSE
            SET fine := (16 * 5) + ((dt2 - 30) * 50);  -- Rs 5 per day for days 15-30, Rs 50 per day for days > 30
        END IF;

        -- Insert fine details into the Fine table
        INSERT INTO fine 
        VALUES (roll, CURDATE(), fine);

        -- Update the status of the book to returned
        UPDATE Borrower 
        SET status = TRUE 
        WHERE roll_no = roll AND book_name = book;
        
    ELSE
        -- If the book has already been returned
        SELECT 'Book has already been returned' AS Message;
    END IF;
END //


DELIMITER ;
