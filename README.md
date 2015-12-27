Spiegazione algoritmo, motivazioni e risultati sono commentati nelle slides

Implementazione di una variante del DBScan discussa nel paper http://fogo.dbs.ifi.lmu.de/Publikationen/Papers/PAKDD04.pdf

Codice C++ single view modificato: http://codingplayground.blogspot.it/2009/11/dbscan-clustering-algorithm.html

ARCardboardBase contiene il progetto Unity per la visualizzazione 3D dei plot (contiene anche l'APK)

slides: http://www.slideshare.net/ginofarisano5/db-scan-multiview


Iter per eseguire gli esperimenti

-eseguire Calculate correlation in result analysis per calcolare la matrice di correlazione sulle viste da analizzare
-eseguire DBscanMultiview in C++ (è consigliabile provare più combinazioni dei parametri eps e minPts)
-eseguire ContourPlotAndBidimensionalPlot*.R (io ho utilizzato due indici) per i plot 2D e 3D (crea anche i modelli 3D). Per il single view fare solo il plot con le line (il grafico 3D non ha senso in questo caso). 
-cancellare cluste banali con CleanFile.R (multiview) e CleanFilesSingleView.R (single view). Eseguire NoiseAfterClean.R per per eseguire delle analisi sui cluster ottenuti dopo il clean
-fare analisi con DBIndex e AngelaIndex
-fare la matrice di confusione con MatriceDiConfusione.R (io l'ho fatto solo per i migliori)

N.B il codice è commmentato abbastanza e "funziona"

Per qualsiasi info contattare gino.farisano@gmail.com

