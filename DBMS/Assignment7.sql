-- Create Library table to store book information
CREATE TABLE Library (
    book_id INT PRIMARY KEY,                -- Primary key for unique identification of each book
    book_name VARCHAR(100),                 -- Name of the book
    author_name VARCHAR(100),               -- Name of the author
    published_year INT                      -- Year the book was published
);

-- Create Library_Audit table to track changes (inserts, updates, deletions) in the Library table
CREATE TABLE Library_Audit (
    audit_id INT AUTO_INCREMENT PRIMARY KEY, -- Unique identifier for each audit record
    book_id INT,                             -- ID of the book being tracked
    book_name VARCHAR(100),                  -- Name of the book being tracked
    author_name VARCHAR(100),                -- Name of the author being tracked
    published_year INT,                      -- Published year of the book being tracked
    operation_type VARCHAR(10)               -- Type of operation ('INSERT', 'UPDATE', 'DELETE')
);

-- BEFORE INSERT trigger to log book details before inserting a new record into the Library table
CREATE TRIGGER before_library_insert
BEFORE INSERT ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (NEW.book_id, NEW.book_name, NEW.author_name, NEW.published_year, 'INSERT');
END;

DELIMITER //
    
-- BEFORE UPDATE trigger to log the old details before updating a record in the Library table
CREATE TRIGGER before_library_update
BEFORE UPDATE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (OLD.book_id, OLD.book_name, OLD.author_name, OLD.published_year, 'UPDATE');
END;

-- BEFORE DELETE trigger to log the old details before deleting a record from the Library table
CREATE TRIGGER before_library_delete
BEFORE DELETE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (OLD.book_id, OLD.book_name, OLD.author_name, OLD.published_year, 'DELETE');
END;

-- AFTER INSERT trigger to log book details after inserting a new record into the Library table
CREATE TRIGGER after_library_insert
AFTER INSERT ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (NEW.book_id, NEW.book_name, NEW.author_name, NEW.published_year, 'INSERT');
END;

-- AFTER UPDATE trigger to log updated details after modifying a record in the Library table
CREATE TRIGGER after_library_update
AFTER UPDATE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (NEW.book_id, NEW.book_name, NEW.author_name, NEW.published_year, 'UPDATE');
END;

-- AFTER DELETE trigger to log deleted book details after removing a record from the Library table
CREATE TRIGGER after_library_delete
AFTER DELETE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, published_year, operation_type)
    VALUES (OLD.book_id, OLD.book_name, OLD.author_name, OLD.published_year, 'DELETE');
END;
