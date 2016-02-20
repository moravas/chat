var gulp = require('gulp');
var webserver = require('gulp-webserver');

gulp.task('run', function() {
  gulp.src('.')
    .pipe(webserver({
      livereload: true,
      directoryListing: false,
      open: true,
      fallback: '/index.html'
    }));
});
