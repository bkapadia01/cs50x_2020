SELECT title, rating FROM movies JOIN ratings ON movies.id=ratings.movie_id WHERE year IS 2010 ORDER BY rating DESC, title ASC
