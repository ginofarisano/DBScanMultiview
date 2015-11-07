# DBScanMultiview

Per analizzare i risultati dell'esperimento  io ho utilizzato R e in particolare il 
pachetto clusterSim che ha vari indici già belli e fatti-> considerare la terza colonna del fileOutput che
è un vettore già bello e pronto da dare in pasto a clusterSim: vedi l'indirizzo
http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.DB.html dove cl1$clustering è proprio quello di cui
sto parlando. Esempio da cui prendere spunto:

Example 1
library(clusterSim)
data(data_ratio)
cl1 <- pam(data_ratio, 4)
d<-dist(data_ratio)
print(index.DB(data_ratio, cl1$clustering,d, centrotypes="medoids"))

Per caricarsi il dataframe vedere il file R console.txt.

Cose da fare (quelle con il visto le sto facendo già io):

V Davies Bouldin

-adJusted rand index

-siluette

-matrice di confusione

istogramma della correlazione intracluster e intercluster

(probabilmente ci sono altre cose da fare così come ha fatto Angela nel paper)



