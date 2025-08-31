/*
 * This query retrieves the IDs of days where the temperature was higher
 * than on the previous day.
 *
 * It uses a self-join on the `Weather` table, aliasing it as `day` and `ystday`
 * (yesterday). The join condition `day.recordDate = DATE_ADD(ystday.recordDate, INTERVAL 1 DAY)`
 * links each day's record to the preceding day's record. The WHERE clause then
 * filters the results to only include days where the temperature for `day`
 * is greater than the temperature for `ystday`.
 */
SELECT
    day.id
FROM
    Weather day
    JOIN Weather ystday
WHERE
    day.recordDate = DATE_ADD(ystday.recordDate, INTERVAL 1 DAY)
    AND day.temperature > ystday.temperature