/*
 * This query retrieves the name, population, and area of countries that
 * are considered large, based on either their total area or their population.
 *
 * It filters the `World` table using a WHERE clause with the OR operator,
 * which selects a country if its area is at least 3,000,000 square kilometers,
 * OR if its population is at least 25,000,000.
 */
SELECT
    name,
    population,
    area
FROM
    World
WHERE
    area >= 3000000
    OR population >= 25000000