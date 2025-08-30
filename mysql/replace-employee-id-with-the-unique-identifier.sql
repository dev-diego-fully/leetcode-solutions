/*
 * This query associates each employee's name with their unique ID by
 * joining the `Employees` and `EmployeeUNI` tables.
 *
 * It uses a LEFT JOIN to ensure that every employee from the `Employees` table
 * is included in the result. If an employee does not have a matching entry
 * in the `EmployeeUNI` table, their `unique_id` will be returned as NULL.
 */
SELECT
    uni.unique_id,
    e.name
FROM
    Employees e
    LEFT JOIN EmployeeUNI uni ON uni.id = e.id