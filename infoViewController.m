//
//  infoViewController.m
//  2333
//
//  Created by pjpjpj on 2017/8/7.
//
//

#import "infoViewController.h"

#ifndef iPhone6﻿
#define iPhone6 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) : NO)
#endif
#ifndef iPhone6P

#define iPhone6P ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) : NO)
#endif

#ifndef iPhone5
#define iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
#endif

@interface infoViewController ()

@end

@implementation infoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIScrollView *scrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    [self.view addSubview:scrollView];
    
    int scrollViewHeigh = 0;
    int btnHeigh = 0;
    if (iPhone5) {
        scrollViewHeigh = 1300;
        btnHeigh = 35;
    } else if (iPhone6) {
        scrollViewHeigh = 1600;
        btnHeigh = 40;
    } else if (iPhone6P) {
        scrollViewHeigh = 1700;
        btnHeigh = 45;
    } else {
        scrollViewHeigh = 1500;
    }
    [scrollView setContentSize:CGSizeMake(self.view.frame.size.width, scrollViewHeigh)];
    
    UIImageView *imgView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, scrollView.contentSize.height)];
    imgView.image = [UIImage imageNamed:@"infoImg"];
    [imgView setUserInteractionEnabled:YES];
    [scrollView addSubview:imgView];
    
    UIButton *backBtn = [[UIButton alloc] initWithFrame:CGRectMake((self.view.frame.size.width - self.view.frame.size.width * 0.6)/2, scrollView.contentSize.height - btnHeigh - 10, self.view.frame.size.width * 0.6, btnHeigh)];
    [backBtn setImage:[UIImage imageNamed:@"backBtn"] forState:UIControlStateNormal];
    [imgView addSubview:backBtn];
    [backBtn addTarget:self action:@selector(bbBtnClick) forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *markBtn = [[UIButton alloc] initWithFrame:CGRectMake((self.view.frame.size.width - self.view.frame.size.width * 0.6)/2, backBtn.frame.origin.y - btnHeigh - 10, self.view.frame.size.width * 0.6, btnHeigh)];
    [markBtn setImage:[UIImage imageNamed:@"markBtn"] forState:UIControlStateNormal];
    [markBtn addTarget:self action:@selector(mmBtnClick) forControlEvents:UIControlEventTouchUpInside];
    [imgView addSubview:markBtn];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)mmBtnClick {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"提示" message:@"到App Store中给我们打分哟！O(∩_∩)O~~" preferredStyle:UIAlertControllerStyleActionSheet];
    // 设置popover指向的item
    alert.popoverPresentationController.barButtonItem = self.navigationItem.leftBarButtonItem;
    
    // 添加按钮
    [alert addAction:[UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        
    }]];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)bbBtnClick {
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}


@end
