#' A MVDA Function
#'
#' This function evaluate the summary intdex for a clustering results
#' @param DB your matrix dataset
#' @param cluster is a numeric vector of clustering results
#' @keywords clustering evaluation
#' @return a vector of evaluation indexes
#' @export


clustering_summary <- function(DB, cluster,maxNumberOfCluster){
  diss.cor <-1- cor(t(DB),method="pearson")
  toPrint <- matrix(0,nrow=1,ncol=5)
  NOBJS = dim(DB)[1]
  
  colnames(toPrint)<- c("#clusters","Intra_avg","inter_complete","Noise","Angela's+++ && Gino's+--- Index")
  
  tab <- table(cluster)
  center = findCenter(DB = DB,clust_vector = cluster)
  j = 1
  toPrint[j,1]<-length(tab)
  
  cls.scatt.diss.mx(diss.mx=diss.cor,clust=cluster) -> clust_eval
  clust_eval$intracls.average -> intra.avg
  clust_eval$intercls.complete -> inter.c
  
  toPrint[j,2] = round(1-mean(intra.avg),digits = 5)
  toPrint[j,3] = round(1-mean(inter.c),digits = 5)
  
  #length Cluster
  lengthCluster<-length(cluster)
  #noise
  lengthNoise<-length(which(cluster==1))
  
  noise<-lengthNoise/lengthCluster
  
  #noise
  toPrint[j,4] = noise
  
                              #1                    #0
  toPrint[j,5] =(1/4) * ( ((toPrint[j,2]+1)/2) + (1-(toPrint[j,3]+1)/2) +
                             + (toPrint[j,1]/maxNumberOfCluster)+(1-noise))
  
  return(round(toPrint,digit=3))
}