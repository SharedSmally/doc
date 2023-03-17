# Node Graphics Library (d3+NVD3/Chart)
- [d3](https://d3js.org/):Data-Driven Documents: A collection of modules:
- [NVD3](https://nvd3.org/): Based on D3
- [C3](https://c3js.org/): based on D3
- [RawGraphs](https://rawgraphs.io/): based on D3 for vector-based visualizations
- [Plotly](https://plot.ly/): based on D3
- [Recharts](https://recharts.org/en-US/): based on D3 using declaritive expression.
- [Chart](https://www.chartjs.org/). 8 Different Chart Types, Small and Simple, using canvas for rendering (Polyfills).
- [Google Chart](https://developers.google.com/chart)
- [Sigma charts](http://sigmajs.org): on Canvas and WebGL

Commercials:
- amCharts: https://www.amcharts.com/javascript-charts/
- FusionCharts: https://www.fusioncharts.com/
- HighCharts: https://www.highcharts.com/


## d3
```
<script src="https://d3js.org/d3.v7.min.js"></script>
```
    - [API](https://github.com/d3/d3/blob/main/API.md)
    - Array
    - Axes
    
## [Chart](https://www.chartjs.org/). Chart Types
    - Area Chart
    - Bar Chart
    - Bubble Chart
    - Doughnut and Pie Charts
    - Line Chart
    - Mixed Chart Types
    - Polar Area Chart
    - Radar Chart
    - Scatter Chart
```
<div>
  <canvas id="myChart"></canvas>
</div>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

<script>
  const ctx = document.getElementById('myChart');
  new Chart(ctx, {
    type: 'bar',
    data: {
      labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
      datasets: [{
        label: '# of Votes',
        data: [12, 19, 3, 5, 2, 3],
        borderWidth: 1
      }]
    },
    options: {
      scales: {
        y: {
          beginAtZero: true
        }
      }
    }
  });
</script>
```
## [Google Chart](https://developers.google.com/chart):
```
<html>
  <head>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['corechart']});
      google.charts.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = new google.visualization.DataTable();
        data.addColumn('string', 'Topping');
        data.addColumn('number', 'Slices');
        data.addRows([
          ['Mushrooms', 3],
          ['Onions', 1],
          ['Olives', 1],
          ['Zucchini', 1],
          ['Pepperoni', 2]
        ]);
        var options = {'title':'How Much Pizza I Ate Last Night',
                       'width':400,
                       'height':300};
        var chart = new google.visualization.PieChart(document.getElementById('chart_div'));
        chart.draw(data, options);
      }
    </script>
  </head>

  <body>
    <div id="chart_div"></div>
  </body>
</html>
```
