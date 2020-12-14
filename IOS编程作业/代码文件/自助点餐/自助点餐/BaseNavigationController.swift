//
//  BaseNavigationController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/19.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit

class BaseNavigationController: UINavigationController, UINavigationControllerDelegate{
    var popDelegate:UIGestureRecognizerDelegate?
    
    override init(rootViewController: UIViewController) {
        super.init(rootViewController: rootViewController)
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: Bundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //navigationBar的背景,字体，字体颜色设置
        self.navigationBar.barTintColor = .red
        self.navigationBar.titleTextAttributes = [NSAttributedString.Key.font:UIFont.systemFont(ofSize: 20), NSAttributedString.Key.foregroundColor:UIColor.white]
        self.navigationBar.tintColor = .white
        
        //返回手势
        self.popDelegate = self.interactivePopGestureRecognizer?.delegate
        self.delegate = self
        
    }
    
// UIGestureRecognizerDelegate代理
    func navigationController(_ navigationController: UINavigationController, didShow viewController: UIViewController, animated: Bool) {
        //实现滑动返回的功能
        //清空滑动返回手势的代理就可以实现
        if viewController == self.viewControllers[0]{
            self.interactivePopGestureRecognizer?.delegate = self.popDelegate
        }else{
            self.interactivePopGestureRecognizer?.delegate = nil
        }
    }
    
//    拦截跳转事件
    override func pushViewController(_ viewController: UIViewController, animated: Bool) {
        if self.children.count > 0{
            viewController.hidesBottomBarWhenPushed = true
            viewController.navigationItem.leftBarButtonItem = UIBarButtonItem(image: UIImage(named: "返回"), style: .plain, target: self, action: #selector(navigationBack))
        }
        super.pushViewController(viewController, animated: true)
    }
    /// 返回上一控制器
    @objc private func navigationBack() {
        popViewController(animated: true)
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}
