

test_x <-(pc.dtwlb@centroids)
test_x <- lapply(test_x, as.double)
test_xx <- list();
test_xy <- list();
for (i in 1:length(test_x[[1]])) {
  test_xx[i] <-  c(test_x[[1]][i]) 
  test_xy[i] <-  c(i) 
}

plot(pc.dtwlb)

plot(test_xy, test_xx, type = "l",col="green", ylim=c(-2,5))