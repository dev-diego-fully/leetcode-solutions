/*
 * This query deletes duplicate rows from the `Person` table, keeping only
 * the record with the lowest ID for each unique email address.
 *
 * It uses a self-join to compare each row with every other row in the table.
 * The join condition `dupl.email = orig.email` identifies records with the
 * same email, while `dupl.id > orig.id` ensures that only the duplicate
 * record (the one with the higher ID) is marked for deletion.
 */
DELETE dupl
FROM
    Person dupl
    JOIN PERSON orig ON dupl.email = orig.email
    AND dupl.id > orig.id