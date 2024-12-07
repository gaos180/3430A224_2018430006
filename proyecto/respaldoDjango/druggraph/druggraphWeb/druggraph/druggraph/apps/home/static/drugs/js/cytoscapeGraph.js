document.addEventListener('DOMContentLoaded', function () {
  console.log("Entra");
    var elements = JSON.parse(document.getElementById('graph-elements').textContent);
  var total_interactions = parseInt(document.getElementById('total-interactions').value);
  if (total_interactions < 200) {
      var elements = JSON.parse(document.getElementById('graph-elements').textContent);

      var cy = cytoscape({
          container: document.getElementById('cyto'), // Seleccionar el div
          elements: elements,
          style: [
              {
                  selector: 'node[type="drug"]',
                  style: {
                      'background-fit': 'contain',
                      'background-image': 'url("/static/img/pill.webp")',
                      'background-color': '#5ce1e6',
                      'label': 'data(label)',
                      'text-outline-color': '#5ce1e6', 
                      'text-outline-width': 1,
                      'width': 200,
                      'height': 200
                  }
              },
              {
                  selector: 'node[type="target"]',
                  style: {
                      'background-fit': 'contain',
                      'background-image': 'url("/static/img/target.webp")',
                      'background-color': '#ffaaaa',
                      'label': 'data(label)',
                      'text-outline-color': '#ffaaaa', 
                      'text-outline-width': 1,
                      'width': 200,
                      'height': 200
                  }
              },
              {
                  selector: 'edge',
                  style: {
                      'width': 2,
                      'label': 'data(label)',
                      'line-color': function(ele) {
                          return colorMap[ele.data('type')] || '#ccc';
                      },
                      'target-arrow-color': function(ele) {
                          return colorMap[ele.data('type')] || '#ccc';
                      },
                      'curve-style': 'bezier',
                      'target-arrow-shape': 'triangle',
                      'source-arrow-shape': 'triangle',
                  }
              }
          ],
          layout: {
              name: 'circle',
              animate: true,
              fit: true,
              padding: 300,
              nodeRepulsion: 4000
          }
      });

      document.getElementById('cyto').style.display = 'block';

      // Función para descargar la imagen como PNG
      document.getElementById('downloadBtn').addEventListener('click', function () {
          var png64 = cy.png({ scale: 3, full: true });
          var downloadLink = document.createElement('a');
          downloadLink.href = png64;
          downloadLink.download = 'druggraph.png';
          document.body.appendChild(downloadLink);
          downloadLink.click();
          document.body.removeChild(downloadLink);
      });

      // Funciones de disposición
      function applyCoseLayout() {
          cy.layout({
              name: 'cose',
              animate: true,
              fit: true,
              padding: 300,
              nodeRepulsion: 4000
          }).run();
      }

      function applyConcentricLayout() {
          cy.layout({
              name: 'concentric',
              animate: true,
              fit: true,
              padding: 300,
              nodeRepulsion: 4000
          }).run();
      }

      function applyCircleLayout() {
          cy.layout({
              name: 'circle',
              animate: true,
              fit: true,
              padding: 300,
              nodeRepulsion: 4000
          }).run();
      }

      function applyBreadthfirstLayout() {
          cy.layout({
              name: 'breadthfirst',
              animate: true,
              fit: true,
              padding: 300,
              nodeRepulsion: 4000
          }).run();
      }

      // Eventos para cambiar la disposición de los nodos
      document.getElementById('btn-cose').addEventListener('change', applyCoseLayout);
      document.getElementById('btn-concentric').addEventListener('change', applyConcentricLayout);
      document.getElementById('btn-circle').addEventListener('change', applyCircleLayout);
      document.getElementById('btn-breadthfirst').addEventListener('change', applyBreadthfirstLayout);
      
  } else {
      console.log("Demasiadas interacciones para mostrar el grafo.");
  }
});
