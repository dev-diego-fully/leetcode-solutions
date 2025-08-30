/*
 * This query retrieves the IDs of products that are both low in fat
 * and recyclable.
 *
 * It filters the `Products` table using a WHERE clause with two conditions
 * linked by the AND operator, ensuring that only products meeting both
 * criteria are included in the final result set.
 */
SELECT
    product_id
FROM
    Products
WHERE
    low_fats = 'Y'
    and recyclable = 'Y'