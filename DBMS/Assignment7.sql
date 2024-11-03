-- Create Library table
CREATE TABLE Library (
    book_id INT PRIMARY KEY,
    book_name VARCHAR(100),
    author_name VARCHAR(100),
    published_year INT
);

-- Create Library_Audit table to track updates and deletions
CREATE TABLE Library_Audit (
    audit_id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT,
    book_name VARCHAR(100),
    author_name VARCHAR(100),
    published_year INT,
    operation_type VARCHAR(10),   -- To track whether it's an 'UPDATE' or 'DELETE'
);

-- Trigger to capture old values before updating the Library table
CREATE TRIGGER before_library_update
BEFORE UPDATE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, genre, published_year, operation_type)
    VALUES (OLD.book_id, OLD.book_name, OLD.author_name, OLD.genre, OLD.published_year, 'UPDATE');
END;

-- Trigger to capture old values before deleting from the Library table
CREATE TRIGGER before_library_delete
BEFORE DELETE ON Library
FOR EACH ROW
BEGIN
    INSERT INTO Library_Audit (book_id, book_name, author_name, genre, published_year, operation_type)
    VALUES (OLD.book_id, OLD.book_name, OLD.author_name, OLD.genre, OLD.published_year, 'DELETE');
END;
