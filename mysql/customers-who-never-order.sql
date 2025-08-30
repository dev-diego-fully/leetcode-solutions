/*
 * This query identifies and retrieves the names of all customers who have not
 * placed any orders.
 *
 * It uses a LEFT JOIN to combine the `Customers` and `Orders` tables.
 * This ensures that every customer is included in the result set, regardless
 * of whether they have an associated order. The `WHERE` clause then filters
 * for records where the `customerId` from the `Orders` table is NULL, which
 * precisely identifies the customers without any orders.
 */
SELECT
    c.name AS Customers
FROM
    Customers AS c
    LEFT JOIN Orders AS o ON c.id = o.customerId
WHERE
    o.customerId IS NULL