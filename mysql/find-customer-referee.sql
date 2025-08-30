/*
 * This query retrieves the names of all customers who were not referred
 * by the customer with ID 2.
 *
 * It uses a WHERE clause with two conditions linked by the OR operator.
 * The first condition, `referee_id != 2`, handles all customers referred
 * by someone other than ID 2. The second condition, `referee_id IS NULL`,
 * is necessary to include customers who were not referred at all, as
 * `NULL` values cannot be compared with a number using the `!=` operator.
 */
SELECT
    name
FROM
    Customer
WHERE
    referee_id != 2
    OR referee_id IS NULL