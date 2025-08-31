/*
 * This query generates a report listing every student, every subject, and the
 * number of exams each student has attended for each subject.
 *
 * It starts by creating a Cartesian product of the `Students` and `Subjects`
 * tables using a CROSS JOIN, which ensures that every possible combination of
 * student and subject is included. A LEFT JOIN is then used to connect this
 * result with the `Examinations` table. This allows us to count the number of
 * exams attended for each student-subject pair. The `COUNT()` function will
 * correctly return zero for pairs where no examination record exists.
 *
 * The results are grouped by student and subject to provide the final counts,
 * and then ordered for readability.
 */
SELECT
    st.student_id,
    st.student_name,
    sb.subject_name,
    COUNT(ex.subject_name) attended_exams
FROM
    Students st
    CROSS JOIN Subjects sb
    LEFT JOIN Examinations ex ON st.student_id = ex.student_id
    AND sb.subject_name = ex.subject_name
GROUP BY
    st.student_id,
    st.student_name,
    sb.subject_name
ORDER BY
    st.student_id,
    sb.subject_name