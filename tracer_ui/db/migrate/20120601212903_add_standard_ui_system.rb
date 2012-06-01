class AddStandardUiSystem < ActiveRecord::Migration
  def up
    ExternalSystem.create!({:name => 'Standard UI', :auth_token => 'BD04130C-AC30-11E1-ACA8-95196288709B'})
  end

  def down
    ExternalSystem.find_by_auth_token('BD04130C-AC30-11E1-ACA8-95196288709B').destroy
  end
end
