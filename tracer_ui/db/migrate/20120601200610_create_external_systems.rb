class CreateExternalSystems < ActiveRecord::Migration
  def change
    create_table :external_systems do |t|
      t.string :name
      t.string :auth_token

      t.timestamps
    end
  end
end
