$NetBSD: patch-mozilla_third__party_rust_libc_src_unix_bsd_netbsdlike_netbsd_other_mod.rs,v 1.2 2021/02/08 12:26:20 ryoon Exp $

Support aarch64.

--- third_party/rust/libc/src/unix/bsd/netbsdlike/netbsd/other/mod.rs.orig	2020-02-17 23:39:18.000000000 +0000
+++ third_party/rust/libc/src/unix/bsd/netbsdlike/netbsd/other/mod.rs
@@ -1,5 +1,6 @@
 cfg_if! {
     if #[cfg(any(target_arch = "sparc64",
+                 target_arch = "aarch64",
                  target_arch = "x86_64"))] {
         mod b64;
         pub use self::b64::*;
