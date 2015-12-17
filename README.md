Spiegazione algoritmo, motivazioni e risultati sono commentati nelle slides

Implementazione di una variante del DBScan discussa nel paper http://fogo.dbs.ifi.lmu.de/Publikationen/Papers/PAKDD04.pdf

Codice C++ single view modificato: http://codingplayground.blogspot.it/2009/11/dbscan-clustering-algorithm.html

ARCardboardBase contiene il progetto Unity per la visualizzazione 3D dei plot (contiene anche l'APK)

slides: http://www.slideshare.net/ginofarisano5/db-scan-multiview


Iter per eseguire gli esperimenti

-eseguire DBscanMultiview in C++
-eseguire ContourPlotAndBidimensionalPlotAngela.R per i plot 2D e 3D (crea anche i modelli 3D). Per il single view è possibile 
fare solo il plot con le line. 
-cancellare cluste banali con CleanFile.R (multiview) e CleanFilesSingleView.R (single view)
-fare analisi con DBIndex e AngelaIndex
-fare la matrice di confusione con MatriceDiConfusione.R (io l'ho fatto solo per i migliori)

N.B il codice è commmentata abbastanza e "funziona

Per qualsiasi info contattare gino.farisano@gmail.com

