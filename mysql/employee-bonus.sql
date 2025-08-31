/*
 * This query retrieves the names of employees along with their bonuses,
 * specifically for those who have a bonus of less than 1000 or no bonus at all.
 *
 * It uses a LEFT JOIN to ensure that every employee from the `Employee` table
 * is included in the result, even if they have no corresponding entry in the
 * `Bonus` table. The `WHERE` clause then filters these results. The condition
 * `b.bonus IS NULL` is crucial to include employees who do not have a bonus.
 */
SELECT
    e.name,
    b.bonus
FROM
    Employee e
    LEFT JOIN Bonus b ON b.empId = e.empId
WHERE
    b.bonus < 1000
    OR b.bonus IS NULL