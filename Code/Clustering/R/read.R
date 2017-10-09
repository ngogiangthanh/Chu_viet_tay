rm(CharTraj, CharTrajLabels, CharTrajMV)
rm(pp, pp_data, wp, wp_data, rs, rs.Idx, rs.val, i, pc.dtwlb, series)

#read projection profiles
pp <- scan("D:\\projection_profiles.txt", what="", sep="\n")
# Separate elements by one or more whitepace
pp_data <- strsplit(pp, "[[:space:]]+")
# Extract the first vector element and set it as the list element name
names(pp_data) <- sapply(pp_data, `[[`, 1)
#names(y) <- sapply(y, function(x) x[[1]]) # same as above
# Remove the first vector element from each list element
pp_data <- lapply(pp_data, `[`, -1)
pp_data <- lapply(pp_data, as.numeric)

#read word profiles
wp <- scan("D:\\word_profiles.txt", what="", sep="\n")
# Separate elements by one or more whitepace
wp_data <- strsplit(wp, "[[:space:]]+")
# Extract the first vector element and set it as the list element name
names(wp_data) <- sapply(wp_data, `[[`, 1)
#names(y) <- sapply(y, function(x) x[[1]]) # same as above
# Remove the first vector element from each list element
wp_data <- lapply(wp_data, `[`, -1)
wp_data <- lapply(wp_data, as.numeric)
