DELETE FROM interaction_dt
WHERE category_id IN (
    SELECT category_id
    FROM (
        SELECT category_id,
               ROW_NUMBER() OVER (PARTITION BY drug_drug_id, target_target_id, type_interaction ORDER BY category_id) AS row_num
        FROM interaction_dt
    ) t
    WHERE t.row_num > 1
);

-- Interacciones droga droga eliminar duplicados incluyendo descripcion
DELETE FROM interaction_dd
WHERE interaction_dd_id IN (
    SELECT interaction_dd_id
    FROM (
        SELECT interaction_dd_id,
               ROW_NUMBER() OVER (PARTITION BY drug_drug_id_1, drug_drug_id_2, description ORDER BY interaction_dd_id) AS row_num
        FROM interaction_dd
    ) t
    WHERE t.row_num > 1
);
-- elimina duplicados donde sea tanto ab o ba en farmaco
WHERE interaction_dd_id IN (
    SELECT interaction_dd_id
    FROM (
        SELECT interaction_dd_id,
               LEAST(drug_drug_id_1, drug_drug_id_2) AS drug_min,
               GREATEST(drug_drug_id_1, drug_drug_id_2) AS drug_max,
               ROW_NUMBER() OVER (PARTITION BY LEAST(drug_drug_id_1, drug_drug_id_2), GREATEST(drug_drug_id_1, drug_drug_id_2), description ORDER BY interaction_dd_id) AS row_num
        FROM interaction_dd
    ) t
    WHERE t.row_num > 1
);

