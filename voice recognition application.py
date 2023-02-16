import logging.handlers

# Create logger
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# Handler 
LOG_FILE = '/tmp/sample-app.log'
handler = logging.handlers.RotatingFileHandler(LOG_FILE, maxBytes=1048576, backupCount=5)
handler.setLevel(logging.INFO)

# Formatter
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

# Add Formatter to Handler
handler.setFormatter(formatter)

# add Handler to Logger
logger.addHandler(handler)

welcome = """
<!doctype html>
<!-- divinectorweb.com -->
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Warriors App</title>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Berkshire+Swash&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="warriorsstyle.css">

<style>
{
	box-sizing: border-box;
	margin: 0;
	padding: 0;
}
body {
	font-family: montserrat;
	background-image: url('https://wallpaperaccess.com/full/5506731.jpg');
    color: #FFFFFF;
}
.section-padding {
	padding: 50px 0;
}
.wrapper {
	width: 1170px;
	margin: 0 auto;
}
header {
	overflow: hidden;
	height: 100vh;
	position: relative;
}
.vid-bg {
	position: absolute;
	right: 0;
	bottom: 0;
	min-width: 100%;
	min-height: 100%;
}
.nav-area {
	background: rgba(0, 0, 0, 0.7);
	height: 60px;
	position: absolute;
	width: 100%;
}
.logo {
	margin: 10px 50px;
	height: 60px;
	float: left;
	color: #fff;
	font-size: 35px;
	text-transform: capitalize;
}
.menu-area {
	float: right;
	list-style: none;
	margin: 20px;
}
.menu-area li {
	display: inline-block;
	margin: 0 5px;
}
.menu-area li a {
	text-decoration: none;
	color: #fff;
	padding: 5px 10px;
	letter-spacing: 2px;
}
.menu-area li.active a {
	color: deepskyblue;
}
.menu-area li a:hover {
	color: deepskyblue;
}
header .welcome-text {
	position: absolute;
	width: 100%;
	text-align: center;
	top: 50%;
	left: 50%;
	transform: translate(-50%, -50%);
}
.welcome-text h2 {
	color: #fff;
	font-size: 80px;
	margin: 0;
	font-family: Berkshire Swash;
}
.welcome-text h3 {
	color: #fff;
	font-size: 60px;
	margin: 0;
	font-family: Berkshire Swash;
}
.welcome-text p {
	color: #fff;
	font-size: 18px;
	width: 45%;
	line-height: 1.8;
	margin: auto;
}
.btn {
	background: #fff;
	border: none;
	color: #000;
	padding: 10px 30px;
	font-size: 15px;
	text-transform: uppercase;
	border-radius: 25px;
	display: inline-block;
	margin-top: 25px;
}
/*responsive*/

@media (min-width: 767px) and (max-width: 991px) {
	.welcome-text p {
		width: 95%;
	}
}
@media (max-width: 767px) {
	.logo {
		float: none;
		text-align: center;
	}
	.menu-area {
		float: none;
		text-align: center;
		margin: 0;
	}
	.menu-area li {
		margin: 0;
	}
	.menu-area li a {
		padding: 5px 2px;
		font-size: 12px;
	}
	.logo {
		margin: 5px 0;
		font-size: 35px;
		height: 45px;
	}
	.nav-area {
		height: 90px;
	}
	.welcome-text h2 {
		font-size: 28px;
		margin-bottom: 18px;
	}
	.welcome-text p {
		width: 90%;
		line-height: 1.5;
	}
}
</style>

</head>
<body>

    <header>
         <!--  <video src="bgwarriors.mp4" class="vid-bg" autoplay loop muted></video> -->
        <div class="nav-area">
            <div class="logo">Warriors</div>

           <!--  <ul class="menu-area">
                <li class="active"><a href="#">Home</a></li>
                <li><a href="#">About</a></li>
                <li><a href="#">Portfolio</a></li>
                <li><a href="#">Contact</a></li>
            </ul> -->
			
        </div>

        <div class="welcome-text">
			<h3> Welcome to</h3>
            <h2>Warriors Web Application</h2>
            <p>Warriors web application for monitoring of real time data coming from the hybrid panels.</p>
			<p>This environment is launched with Elastic Beanstalk Python Platform.</p>
            
    <button class="btn">Back end (IoT Core) </button>
    <button class="btn"onclick="window.location.href='https://sites.google.com/my.jru.edu/warriors/home';">Monitoring System </button>
     <button class="btn"onclick="window.location.href='https://us-east-1.quicksight.aws.amazon.com/sn/start?';">Mock Data </button>
    <button class="btn"onclick="window.location.href='https://gelannicolan.wixsite.com/website';">About Us </button>
       
        </div>
    </header>   

</body>

</html>
"""


def application(environ, start_response):
    path = environ['PATH_INFO']
    method = environ['REQUEST_METHOD']
    if method == 'POST':
        try:
            if path == '/':
                request_body_size = int(environ['CONTENT_LENGTH'])
                request_body = environ['wsgi.input'].read(request_body_size)
                logger.info("Received message: %s" % request_body)
            elif path == '/scheduled':
                logger.info("Received task %s scheduled at %s", environ['HTTP_X_AWS_SQSD_TASKNAME'],
                            environ['HTTP_X_AWS_SQSD_SCHEDULED_AT'])
        except (TypeError, ValueError):
            logger.warning('Error retrieving request body for async work.')
        response = ''
    else:
        response = welcome
    start_response("200 OK", [
        ("Content-Type", "text/html"),
        ("Content-Length", str(len(response)))
    ])
    return [bytes(response, 'utf-8')]
