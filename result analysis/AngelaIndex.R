#calcola calcola un indice di bontà dei cluster a seconda della correlazione nei cluster e fuori dai cluster.
#Angela's index è un numero compreso tra 0 e 1 (1 è migliore di 0)
source("clustering_summary.R")
source("findCenter.R")

library(clv)

#questo script legge i risultati prodotti dall'algoritmo DBScanMultiview e produce in output
#un' analisi dei risultati
#ATTENZIONE: QUESTO SCRIPT DEVE ESSERE ESEGUITO DOPO AVER LANCIATO CleanFiles.R (L'OUTPUT DI DBScanMultiview CONTIENE MOLTI
#RISULTATI INUTILI CHE E' MEGLIO SCARTARE...LA PATH DI resultAngelaIndexSCAN DEVE ESSERE howToSave IN CleanFiles.R )

library(clusterSim)

####################### MODIFICARE QUESTI PARAMETRI PER ESEGUIRE L'ANALISI SU DATI DIFFERENTI ######################

#modificare i due valori in base a quelli impostati in DBScanMultiview
minPTSStart = 4
minPTSStop = 25

#dove stampo i risultati?
pathOutputPDF = "~/Desktop/progetto IAC/singleView correlation2/"

#dataset iniziale
#correlation1
#dataset1 <- "~/Desktop/progetto IAC/kmeans_miRNASeq_centers.txt"
#correlation2
dataset1 <- "~/Desktop/progetto IAC/kmeans_miRNA_centers.txt"


#output risulatati DBScanMultiview
resultAngelaIndexSCAN <- "~/Desktop/progetto IAC/outputSingleViewCorrelation2New.csv"

#quanti plot che hanno il miglior risultato voglio salvare?
numberOfPlotBest<-2

####################### MODIFICARE QUESTI PARAMETRI PER ESEGUIRE L'ANALISI SU DATI DIFFERENTI ######################

####################### LETTURA DATI ######################
mydata1 = read.table(dataset1)
mydata1 = scale(mydata1)
#trasposta della matrice
mydata1 <- t(mydata1)
#trasformo in un dataframe
mydata1<-as.data.frame(mydata1)
View(mydata1)

#leggo i risultati dell'unione o intersezione
dataUnionOrIntersection <- read.table(resultAngelaIndexSCAN, header=FALSE, sep=";")
#prendo la quarta colonna che sono i clusters
clustersUnionOrIntersection <- dataUnionOrIntersection[,4]

#altre colonne
eps1Iteration <- dataUnionOrIntersection[,1]
eps2Iteration <- dataUnionOrIntersection[,2]
minPtsIteration <- dataUnionOrIntersection[,3]
#altre colonne

numberOfIterations=length(dataUnionOrIntersection[,4])

####################### LETTURA DATI ######################

####################### CALCOLO AngelaIndex INDEX ######################

maxMy<--1

#massimo numero di cluster nel clustering
for(cluster in clustersUnionOrIntersection){
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  #metto delle label->vedi cl1$clustering in Example1 in http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.DB.html
  myCluster <- setNames(myCluster, 1:length(myCluster))
  
  myMax<-length(table(myCluster))
  
  if(myMax>maxMy)
    maxMy<-myMax
  
}


#stampo i risultadi del AngelaIndex index
result <- c()

i = 1

pb = txtProgressBar(min = 1, max = length(clustersUnionOrIntersection),style = 3)

#first dataset
for(cluster in clustersUnionOrIntersection){
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  #metto delle label->vedi cl1$clustering in Example1 in http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.AngelaIndex.html
  myCluster <- setNames(myCluster, 1:length(myCluster))
  
  #index.AngelaIndex (il cluster 0 è rumore pertanto aggiungo sempre +1-> a index.AngelaIndex altrimenti non gli piace)
  index_res = clustering_summary(mydata1, myCluster+1,as.numeric(maxMy))
  
  #metto l'indice in un lista
  result <- c(result,index_res[5])
  
  setTxtProgressBar(pb,i)
  i = i+1
}

close(pb)

####################### CALCOLO AngelaIndex INDEX ######################

#indici Na (probabilmente perchè tutti i punti sono nello stesso cluster)
indexBad = which(is.na(result)==TRUE)
#indici buoni
indexGood = which(is.na(result)==FALSE)

maxValue<-max(result[indexGood])

maxIndex<-which(result==max(result[indexGood]))

####################### STAMPO IL MASSIMO ######################
for(myMaxIndex in maxIndex)
  print(paste(dataUnionOrIntersection[myMaxIndex,1],dataUnionOrIntersection[myMaxIndex,2],dataUnionOrIntersection[myMaxIndex,3],dataUnionOrIntersection[myMaxIndex,4],result[myMaxIndex]))



#I select only the first
myCluster <- as.integer(unlist(strsplit(as.character(dataUnionOrIntersection[maxIndex[1],4])," ")))

dataframe<-data.frame(dataUnionOrIntersection[maxIndex[1],1],dataUnionOrIntersection[maxIndex[1],2],dataUnionOrIntersection[maxIndex[1],3],dataUnionOrIntersection[maxIndex[1],4],result[maxIndex[1]],paste(rownames(table(myCluster)),":",table(myCluster),collapse="-"))

colnames(dataframe)<-c("eps1","eps2","minPts","Cluster","AngelaIndex","Tabella di contingenza")

write.table(dataframe,file=paste(pathOutputPDF,"minimoAngelaIndex.csv"),row.names = FALSE,sep=";",quote=FALSE)


####################### STAMPO IL MASSIMO ######################

####################### STAMPO PER ORDINE AngelaIndex ######################

xAxis<-c()
yAxis <-c()
contigencyTableAll <- c()
rowNumberInResults <- c()
clusterData<-c()

for(index in indexGood){
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  cluster = as.vector(clustersUnionOrIntersection[index])
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  #costruisco una tabella di contingenza e la trasformo in un dataframe
  
  clusterData<-c(clusterData,cluster)
  
  contigencyTable<-as.data.frame(table(myCluster))
  #asse x
  xAxis<-c(xAxis,numsClust<-max(as.numeric(contigencyTable[,1])))
  #asse y
  yAxis <-c(yAxis,result[index])
  
  contigencyTableCluster <- c()
  
  for(row in 1:dim(contigencyTable)[1]){
    contigencyTableCluster <-c(contigencyTableCluster, paste(contigencyTable[row,1],":",contigencyTable[row,2]))
  }
  
  contigencyTableAll <- c(contigencyTableAll,paste(contigencyTableCluster,collapse = ","))
  
  rowNumberInResults <- c(rowNumberInResults,index)
  
}

pdf(paste(sep="",pathOutputPDF,"plotAngelaIndex1.pdf"))

plot(xAxis, yAxis,  xaxt="n",xlab="Number of clusters", ylab="Angela's+++ && Gino's+--- Index", ,main="Angela's+++ && Gino's+--- Index (for number of clusters)",pch=16)

axis(1, at=unique(xAxis),labels=unique(xAxis))

dev.off()

fd <- data.frame(xAxis,yAxis,contigencyTableAll,rowNumberInResults,clusterData)

colnames(fd)<-c("Numero di Clusters","AngelaIndex","Individui per cluster (Numero cluster: numero elementi)","Numero di riga","Cluster")

View(fd)

#ordino per AngelaIndex prendo e prendo i tre più piccoli AngelaIndex per numero di clusters
#ne metto
order.pop <- order(fd$`Numero di Clusters`,-fd$`AngelaIndex`)

View(fd[order.pop,])

write.table(fd[order.pop,],file=paste(pathOutputPDF,"AngelaIndexOrdered.csv"),sep=";",row.names = FALSE)

####################### STAMPO PER ORDINE AngelaIndex ######################

####################### STAMPO PER ORDINE AngelaIndex DIVISI PER CLASSI ######################

#numero di cluster massimo
maxNumberOfCluster<- max(xAxis)

#tanti contatori quanti sono i clusters possibili in output
listOfCounter<- c(rep(0,maxNumberOfCluster))

myListOfIndexBest <-c()

firstIteration = TRUE

for(index in order.pop)
  #mi interessa da due cluster in poi
  for(number in 2:maxNumberOfCluster){
    #ne prendo 3 per ogni classe di cluster
    #molti dei cluster sono uguali quindi ci metto l'ulteriore vincolo che 2 cluster
    #non devono essere uguali
    
    #  modificare listOfCounter[number]<3 se invece dei 3 migliori se ne vogliono prendere di più o di meno                    
    if(fd[index,1]==number && listOfCounter[number]<numberOfPlotBest && length(intersect(fd[index,3],fd[myListOfIndexBest,3]))==0){
      myListOfIndexBest <- c(myListOfIndexBest,index)
      listOfCounter[number]= listOfCounter[number]+1
      break
    }
    
  }

View(fd[myListOfIndexBest,])

write.table(fd[myListOfIndexBest,],file=paste(pathOutputPDF,"AngelaIndexOrderedXForClass.csv"),sep=";",row.names = FALSE)

#per i migliori disegno un grafico
group <- 0

stringPie <- "pieAngelaIndex"

forPrintPDFPieCounter <- 1

pdf(paste(pathOutputPDF,stringPie,forPrintPDFPieCounter,".pdf",sep = ""),width=15, height=6)
par(mfcol=c(2,2))

for(index in fd[myListOfIndexBest,4]){
  
  if(group==2){
    
    dev.off()
    
    forPrintPDFPieCounter = forPrintPDFPieCounter + 1
    
    pdf(paste(pathOutputPDF,stringPie,forPrintPDFPieCounter,".pdf",sep = ""),width=15, height=6)
    par(mfcol=c(2,2))
    group <- 0
    
  }
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  cluster = as.vector(clustersUnionOrIntersection[index])
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  #costruisco una tabella di contingenza ela trasformo in un dataframe
  contigencyTable<-as.data.frame(table(myCluster))
  print(contigencyTable)
  freqRel <- round(contigencyTable[,2]/sum(contigencyTable[,2])*100,1)
  pi<-pie(freqRel,labels=paste("Cluster",1:length(freqRel),",",freqRel,"%"),main = paste(dataUnionOrIntersection[index,1],dataUnionOrIntersection[index,2],dataUnionOrIntersection[index,3]))
  
  dataForBoxPlot<-clustering_summary(mydata1, myCluster+1,as.numeric(maxMy))
  
  bp<-barplot(as.vector(dataForBoxPlot),col = rainbow(length(dataForBoxPlot)), names.arg=colnames(dataForBoxPlot),ylim = c(0,7),cex.names=0.8)
  text(x=bp,dataForBoxPlot,labels=dataForBoxPlot,pos=3)
  
  group=group+1
  
}

dev.off()

####################### STAMPO PER ORDINE AngelaIndex DIVISI PER CLASSI ######################

####################### BOXPLOT WITH LABEL ######################

source("boxPlot.R")

colors <- rainbow((minPTSStop-minPTSStart)) 

pdf(paste(pathOutputPDF,"boxPlotWithLabelAngelaIndex",".pdf",sep = ""))

#par(mfrow=c(2,2))

maxAngelaIndex=max(result)
minAngelaIndex=min(result)

count<-0

# add lines 
for (i in minPTSStart:minPTSStop) {
  
  #CleanFiles.R è implementato in modo da evitare clusters ridondanti
  
  indexMinPts <- which(dataUnionOrIntersection[,3]==paste("minPts=",i,sep = ""))
  
  df <- data.frame(result[indexMinPts],clustersUnionOrIntersection[indexMinPts])
  
  row.names(df) <- paste(eps1Iteration[indexMinPts],eps2Iteration[indexMinPts])
  
  print(paste("MinPTS",i))
  
  if(length(indexMinPts)>4)
    plot.boxplot(df,1,names=paste("MinPts=",i),color=colors[i],limMin=minAngelaIndex,limMax=maxAngelaIndex)
  
  count <- count + 1
  
} 

dev.off()

####################### BOXPLOT WITH LABEL ######################

####################### BOXPLOT WITHOUT LABEL ######################

source("boxPlot.R")

colors <- rainbow((minPTSStop-minPTSStart)) 

pdf(paste(pathOutputPDF,"boxPlotWithOutLabelAngelaIndex",".pdf",sep = ""))

par(mfrow=c(3,3))

maxAngelaIndex=max(result)
minAngelaIndex=min(result)

# add lines 
for (i in minPTSStart:minPTSStop) {
  
  #CleanFiles.R è implementato in modo da evitare clusters ridondanti
  
  indexMinPts <- which(dataUnionOrIntersection[,3]==paste("minPts=",i,sep = ""))
  
  df <- data.frame(result[indexMinPts],clustersUnionOrIntersection[indexMinPts])
  

  if(length(indexMinPts)>4)
    plot.boxplot(df,1,names=paste("MinPts=",i),color=colors[i],limMin=minAngelaIndex,limMax=maxAngelaIndex,labelFlag=FALSE)  
  
} 

dev.off()

####################### BOXPLOT WITHOUT LABEL ######################