/*
 * This query finds and lists all email addresses that appear more than once
 * in the `Person` table, effectively identifying duplicate entries.
 *
 * It groups the rows by the `email` column and then uses the `HAVING` clause
 * to filter these groups, keeping only those where the count of emails is
 * greater than one.
 */
SELECT
    email
FROM
    Person
GROUP BY
    email
HAVING
    count(email) > 1