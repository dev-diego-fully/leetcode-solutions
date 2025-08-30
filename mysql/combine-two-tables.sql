/*
 * This query retrieves the full name, city, and state of individuals
 * from the Person and Address tables.
 *
 * It performs a LEFT JOIN on the Person table with the Address table
 * based on the `personId` column. This ensures that all individuals
 * from the Person table are included in the result, even if they do not
 * have a corresponding entry in the Address table.
 */
SELECT
    p.firstName, p.lastName, a.city, a.state
FROM
    Person as p left join Address as a
ON
    p.personId = a.personId