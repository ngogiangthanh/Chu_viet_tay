

test_x <-(pc.dtwlb@centroids)
test_x <- lapply(test_x, as.double)
value<- list();
length <- list();
for (i in 1:length(test_x[[1]])) {
  value[i] <-  c(test_x[[1]][i]) 
  length[i] <-  c(i) 
}

plot(pc.dtwlb)

plot(length, value, type = "l",col="green", ylim=c(-2,5))