var gulp = require('gulp');
var webserver = require('gulp-webserver');
var qunit = require('gulp-qunit');

gulp.task('run', function() {
  gulp.src('.')
    .pipe(webserver({
      livereload: true,
      directoryListing: false,
      open: true,
      fallback: '/index.html'
    }));
});

gulp.task('web-tests', function() {
    return gulp.src('./tests/login.html')
        .pipe(qunit());
});