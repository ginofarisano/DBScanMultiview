#matrice di confusione per i "migliori"


library(caret)
source("confusion_matrix.R")

#settare working directory minimi

myMinFile<-c( " minimoAngelaIndexIntersCor1.csv",
              " minimoAngelaIndexIntersCor2.csv",
              " minimoAngelaIndexSingleCor1.csv",
              " minimoAngelaIndexSingleCor2.csv",
              " minimoAngelaIndexUnionCor1.csv",
              " minimoAngelaIndexUnionCor2.csv",
              " minimoDBIndexIntersCor1.csv",
              " minimoDBIndexIntersCor2.csv",
              " minimoDBIndexSingleCor1.csv",
              " minimoDBIndexSingleCor2.csv",
              " minimoDBIndexUnionCor1.csv",
              " minimoDBIndexUnionCor2.csv")

#correlation1
dataset1 <- "kmeans_miRNASeq_centers.txt"
#correlation2
dataset2 <- "kmeans_miRNA_centers.txt"

infoClasses<- read.delim("patient_classes.txt")

mydata1 = read.table(dataset1)
mydata2 = read.table(dataset2)

mydata1 <- t(mydata1)
mydata2 <- t(mydata2)

for(myMin in myMinFile){
  
  all<-read.csv(myMin, sep=";")
  
  #clustering
  cluster<-all[4]
  
  cluster<-as.matrix(cluster)
  
  #trasformo lista di stringhe del tipo "1" "0"... in 1 0
  myCluster <- as.integer(unlist(strsplit(cluster," ")))
  
  #metto delle label->vedi cl1$clustering in Example1 in http://artax.karlin.mff.cuni.cz/r-help/library/clusterSim/html/index.DB.html
  myCluster <- setNames(myCluster, 1:length(myCluster))
  
  nCenter<-length(table(myCluster))
  
  #correlation1
  if(grepl("1",myMin)){
    my_pazienti_geni = mydata1
  } else{#correlation2
    my_pazienti_geni = mydata2
  }
  
  pazienti_geni = mydata1
  cm_km <- confusion_matrix(etichette = infoClasses$x,
                            clustering = myCluster+1,
                            pazienti_geni = my_pazienti_geni ,
                            nCluster = nCenter)
  
  #km2<-confusionMatrix(as.factor(myCluster),as.factor(infoClasses$x))
  
  pdf(paste(myMin,"ConfusionMatrix",".pdf",sep = ""))
  
  
  par(mfrow=c(1, 1), mar=c(5, 5, 4, 8))

  bp<-barplot(cm_km,col = rainbow(dim(cm_km)[1]),xlab="Classi",ylab="Numero di elementi (per Cluster)",legend.text = TRUE,args.legend = list(x = "topright", bty = "n", inset=c(-0.2, 0)))
  
  print(myMin)
  print(cm_km)
  
  dev.off()

  
}

