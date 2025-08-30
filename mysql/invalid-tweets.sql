/*
 * This query retrieves the IDs of all tweets that have a content length
 * greater than 15 characters.
 *
 * It uses the `LENGTH()` function to determine the number of characters in
 * the `content` column for each row and then filters the results based on
 * the specified condition.
 */
SELECT
    tweet_id
FROM
    Tweets
WHERE
    LENGTH(content) > 15