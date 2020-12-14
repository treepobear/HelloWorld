//
//  BaseTabBarController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/19.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit

class BaseTabBarController: UITabBarController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let tabbar = UITabBar.appearance()
        
        tabbar.tintColor = UIColor.red
        tabbar.barTintColor = UIColor.white
        /// 添加子控制器
        addChildViewControllers()
    }
    
    /// 设置控制器
    private func setChildController(controller: UIViewController, imageName: String) {
        controller.tabBarItem.image = UIImage(named: imageName + "_nor")
        controller.tabBarItem.selectedImage = UIImage(named: imageName + "_pre")
    }
    /// 添加子控制器
    private func addChildViewControllers() {
        setChildViewController(RestaurantViewController(), title: "餐厅", imageName: "canting")
        setChildViewController(OrderViewController(), title: "订单", imageName: "dingdan")
    }
    /// 初始化子控制器
    private func setChildViewController(_ childController: UIViewController, title: String, imageName: String) {
        // 设置 tabbar 文字和图片
        setChildController(controller: childController, imageName: imageName)
        childController.title = title
        // 添加导航控制器为 TabBarController 的子控制器
        addChild(BaseNavigationController(rootViewController: childController))
    }
    
    deinit {
        NotificationCenter.default.removeObserver(self)
    }
    
}
