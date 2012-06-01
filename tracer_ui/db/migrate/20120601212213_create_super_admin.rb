class CreateSuperAdmin < ActiveRecord::Migration
  def up
    User.create!({:login => 'admin', :password => 'admin'})
  end

  def down
    User.find_by_login('admin').destroy
  end
end
