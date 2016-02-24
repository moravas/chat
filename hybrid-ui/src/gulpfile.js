var gulp = require('gulp');
var webserver = require('gulp-webserver');
var qunit = require('gulp-qunit');
var ts = require('gulp-typescript');
var sourcemaps = require('gulp-sourcemaps');

gulp.task('build', function() {
  var tsProject = ts.createProject('tsconfig.json');
  
  return tsProject.src()
             .pipe(sourcemaps.init())
             .pipe(ts(tsProject))     
             .js
             .pipe(sourcemaps.write())
             .pipe(gulp.dest('js'));
});

gulp.task('web-tests', ['dist'], function() {
    return gulp.src('../tests/login.html')
               .pipe(qunit());
});

gulp.task('run-dev', function() {
  gulp.src('.')
    .pipe(webserver({
      livereload: true,
      directoryListing: false,
      open: true,
      fallback: '/index.html'
    }));
});

gulp.task("dist", ['build'], function() {
   gulp.src('./bower_components/**').pipe(gulp.dest('../dist/bower_components'));
   gulp.src('./index.html').pipe(gulp.dest('../dist'));
   gulp.src('./css/*.css').pipe(gulp.dest('../dist/css'));
   gulp.src('./js/*.js').pipe(gulp.dest('../dist/js'));
});

gulp.task('run-dist', ['dist'], function() {
  gulp.src('../dist')
    .pipe(webserver({
      livereload: false,
      directoryListing: false,
      open: true,
      fallback: '/index.html'
    }));
});

