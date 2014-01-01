from bottle import route, run, template,static_file
from temperature import *

@route('/')
def index():
	return '''
<!DOCTYPE html>
<html>
<head>
    <script language="javascript" type="text/javascript" src="/static/jquery.min.js"></script>
    <script language="javascript" type="text/javascript" src="/static/jquery.jqplot.min.js"></script>
    <script type="text/javascript" src="/static/jqplot.dateAxisRenderer.min.js"></script>
    <link rel="stylesheet" type="text/css" href="/static/jquery.jqplot.min.css" />
    <script type="text/javascript">
    
        $(document).ready(function() {
		RefreshTemperature();
        var chart;
        $.get('historicData', function(data) {
                var arrayData = eval(data)
                chart = $.jqplot('chartdiv',[arrayData],{
                    title:'Temperature',
                    axes:{xaxis:{renderer:$.jqplot.DateAxisRenderer,
                                 tickOptions: {formatString: '%#d %b, %R'},
                                 numberTicks: 7}}
                });
        });
     	
        var myVar=setInterval(function(){RefreshTemperature()},30000);

		function RefreshTemperature()
		{
			$.get('currentTemperature', function(data) {
				document.getElementById("temperature").innerHTML=data;
			});
            
			$.get('historicData', function(data) {
                var arrayData = eval(data);
                if(chart)
                {
                    chart.data = [arrayData];
                    chart.replot( { resetAxes: true } );
                }
            });
            
		}
        });
    </script>
</head>
<body>
	Temperature: <b id="temperature"></b>
	<div id="chartdiv"></div>
</body>
</html>
'''

@route('/static/<filepath:path>')
def server_static(filepath):
    return static_file(filepath, root='/root/static/')

@route('/currentTemperature')
def currentTemperature():
    return str(temperature())

@route('/historicData')
def historicData():
    content = "["
    with open('./temperature.csv') as file:
        for line in file:
            value = line.split(',')
            content = content + "['{0}',{1}],".format(value[0], value[1])
    content = content[:-1] + "]"
    return content

run(reloader=True, host='192.168.0.21', port=8080)
