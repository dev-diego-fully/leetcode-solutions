/*
 * This query retrieves the name, year, and price for each product sale
 * by combining data from the `Product` and `Sales` tables.
 *
 * It uses an INNER JOIN on the common `product_id` column to match product
 * information with its corresponding sales records.
 */
SELECT
    p.product_name,
    s.year,
    s.price
FROM
    Product p
    JOIN Sales s ON s.product_id = p.product_id