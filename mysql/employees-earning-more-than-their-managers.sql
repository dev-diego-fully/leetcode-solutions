/*
 * This query retrieves the names of all employees who earn more than their direct manager.
 *
 * It performs a self-join on the `Employee` table, aliasing it as `e` for employees
 * and `m` for managers. The join links each employee to their respective manager
 * based on the `managerId` and `id` columns.
 *
 * The WHERE clause filters the results, selecting only those employees
 * whose salary is strictly greater than their manager's salary.
 */
SELECT
    e.name as Employee
FROM
    Employee as e join Employee as m
ON
    e.managerId = m.id
WHERE
    e.salary > m.salary