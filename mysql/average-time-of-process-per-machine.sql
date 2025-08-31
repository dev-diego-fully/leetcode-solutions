/*
 * This query calculates the average processing time for each machine.
 *
 * It uses a self-join on the `Activity` table to pair the `start` and `end`
 * activities of each process. The join condition ensures that a start event is
 * correctly matched with its corresponding end event on the same machine.
 *
 * The processing time is calculated as the difference between the end and start
 * timestamps. The result is then averaged for each machine using `GROUP BY`,
 * and cast to a decimal with three decimal places for a precise output.
 */
SELECT
    s.machine_id,
    CAST(AVG(e.timestamp - s.timestamp) AS DECIMAL(10, 3)) processing_time
FROM
    Activity s
    JOIN Activity e ON s.process_id = e.process_id
    AND s.machine_id = e.machine_id
WHERE
    s.activity_type = 'start'
    AND e.activity_type = 'end'
GROUP BY
    s.machine_id