/*
 * This query retrieves the unique IDs of all authors who have viewed their
 * own articles.
 *
 * The WHERE clause filters the `Views` table to include only the records
 * where the `author_id` and `viewer_id` are the same, indicating a self-view.
 * The `GROUP BY` clause then ensures that each author's ID appears only once
 * in the result set, and the `ORDER BY` clause sorts the final list by ID.
 */
SELECT
    author_id id
FROM
    Views
WHERE
    author_id = viewer_id
GROUP BY
    author_id
ORDER BY
    author_id