library(clusterSim)
library(clv)
cl1 <- pam(mydata1, 4)
clust <- cl1$clustering
cls.scatt.data(mydata1, clust, dist="manhattan")
