//
//  RestaurantCell.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/19.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit

class RestaurantCell: UITableViewCell {

    @IBOutlet weak var res_image: UIImageView!
    @IBOutlet weak var res_label: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
