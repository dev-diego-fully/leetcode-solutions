/*
 * This query counts the number of visits that did not result in a transaction
 * for each customer.
 *
 * It uses a LEFT JOIN from the `Visits` table to the `Transactions` table,
 * which ensures that every visit is included. The WHERE clause then filters
 * for visits that do not have a matching transaction record (`t.transaction_id IS NULL`),
 * and the `GROUP BY` clause aggregates these counts for each unique customer.
 */
SELECT
    v.customer_id,
    COUNT(v.visit_id) as count_no_trans
FROM
    Visits v
    LEFT JOIN Transactions t ON t.visit_id = v.visit_id
WHERE
    t.transaction_id IS NULL
GROUP BY
    v.customer_id